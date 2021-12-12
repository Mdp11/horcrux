#include "horcrux_loader.hpp"

#include <memory>
#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>

#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

#include "horcrux_load_exception.hpp"

horcrux::HorcruxLoader::HorcruxLoader(std::string decryption_key,
									  std::vector<std::string> horcruxes_paths,
									  std::string output_file)
	: decryption_key_{std::move(decryption_key)}, horcruxes_paths_{std::move(horcruxes_paths)},
	  output_file_{std::move(output_file)}
{}

void horcrux::HorcruxLoader::loadHorcruxes()
{
	checkInputs();
	decodeKey();
	join();
	decrypt();
}

void horcrux::HorcruxLoader::checkInputs()
{
	for (const auto &path: horcruxes_paths_)
	{
		if (!std::filesystem::exists(path))
		{
			throw HorcruxLoadException(path + " does not exist");
		}
		if (std::filesystem::is_directory(path))
		{
			throw HorcruxLoadException(path + " is not a file");
		}
	}
}

void horcrux::HorcruxLoader::decodeKey()
{
	const auto predicted_length = 3 * decryption_key_.length() / 4;

	const auto output_buffer{std::make_unique<char[]>(predicted_length + 1)};

	const std::vector<unsigned char> chars{decryption_key_.begin(), decryption_key_.end()};

	const auto output_length = EVP_DecodeBlock(reinterpret_cast<unsigned char *>(output_buffer.get()),
											   chars.data(),
											   static_cast<int>(chars.size()));

	if (predicted_length != static_cast<unsigned long>(output_length))
	{
		throw HorcruxLoadException("error decoding key from base64");
	}

	std::string key = output_buffer.get();

	std::copy(key.begin(), key.end(), decoded_key_.begin());
}

void horcrux::HorcruxLoader::join()
{

	std::ofstream joined_file{"tmp", std::ios::binary};
	if (joined_file.fail())
	{
		throw HorcruxLoadException("error creating joined file");
	}

	std::array<char, MAX_RW_BYTES> buffer{};

	for (const auto &horcrux_path: horcruxes_paths_)
	{
		std::uintmax_t horcrux_size = std::filesystem::file_size(horcrux_path);
		std::uintmax_t rw_size = std::min(horcrux_size, MAX_RW_BYTES);

		std::ifstream horcrux_file{horcrux_path, std::ios::binary};

		if (horcrux_file.fail())
		{
			throw HorcruxLoadException(std::string{"error opening " + horcrux_path});
		}

		for (unsigned int j = 0; j < horcrux_size / rw_size; ++j)
		{
			horcrux_file.read(buffer.data(), rw_size);
			joined_file.write(buffer.data(), horcrux_file.gcount());
		}

		if (horcrux_size % rw_size != 0)
		{
			horcrux_file.read(buffer.data(), horcrux_size % rw_size);
			joined_file.write(buffer.data(), horcrux_file.gcount());
		}

		horcrux_file.close();
	}

	joined_file.close();
}

void horcrux::HorcruxLoader::decrypt()
{
	std::unique_ptr<AES_KEY> aes_key = std::make_unique<AES_KEY>();
	AES_set_decrypt_key(decoded_key_.data(), 256, aes_key.get());

	std::ifstream input("tmp", std::ios::binary);
	if (input.fail())
	{
		throw HorcruxLoadException("error opening joined file");
	}

	//TODO: create directories up to output_file if they do not exist

	std::ofstream output(output_file_, std::ios::binary);
	if (output.fail())
	{
		throw HorcruxLoadException("error creating output file");
	}

	std::array<unsigned char, AES_BLOCK_SIZE> input_bytes;
	std::array<unsigned char, AES_BLOCK_SIZE> output_bytes;

	while (input.peek() != EOF)
	{
		input.read(reinterpret_cast<char *>(input_bytes.data()), AES_BLOCK_SIZE);

		AES_decrypt(input_bytes.data(), output_bytes.data(), (const AES_KEY *)aes_key.get());

		output.write(reinterpret_cast<char *>(output_bytes.data()), input.gcount());
	}

	input.close();
	output.close();

	std::filesystem::remove("tmp");
}
