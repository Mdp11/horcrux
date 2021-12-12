#include "horcrux_loader.hpp"

#include <iostream>
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

	std::ofstream joined_file{TMP_FILE, std::ios::binary};
	if (joined_file.fail())
	{
		throw HorcruxLoadException("error creating joined file");
	}

	std::array<char, MAX_RW_BYTES> buffer{};

	for (std::size_t i = 0;  i < horcruxes_paths_.size(); ++i)
	{
		std::cout << "\rJoining horcrux " << i + 1 << "/" << horcruxes_paths_.size() << "..." << std::flush;

		std::uintmax_t horcrux_size = std::filesystem::file_size(horcruxes_paths_.at(i));
		std::uintmax_t rw_size = std::min(horcrux_size, MAX_RW_BYTES);

		std::ifstream horcrux_file{horcruxes_paths_.at(i), std::ios::binary};

		if (horcrux_file.fail())
		{
			throw HorcruxLoadException(std::string{"error opening " + horcruxes_paths_.at(i)});
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

	std::cout << std::endl << "Joined all horcruxes!" << std::endl;

	joined_file.close();
}

void horcrux::HorcruxLoader::decrypt()
{
	std::unique_ptr<AES_KEY> aes_key = std::make_unique<AES_KEY>();
	AES_set_decrypt_key(decoded_key_.data(), 256, aes_key.get());

	std::uintmax_t file_size = std::filesystem::file_size(TMP_FILE);
	std::uintmax_t total_chunks = file_size / AES_BLOCK_SIZE;
	std::uintmax_t current_chunk{1};
	std::uintmax_t current_percent{0};

	std::ifstream input(TMP_FILE, std::ios::binary);
	if (input.fail())
	{
		throw HorcruxLoadException("error opening joined file");
	}

	std::filesystem::path output_path{output_file_};
	std::filesystem::path parent_path = output_path.parent_path();

	if(!parent_path.empty())
	{
		std::filesystem::create_directories(parent_path);
	}

	std::ofstream output(output_file_, std::ios::binary | std::ios::trunc);
	if (output.fail())
	{
		throw HorcruxLoadException("error creating output file " + output_file_);
	}

	std::array<unsigned char, AES_BLOCK_SIZE> input_bytes;
	std::array<unsigned char, AES_BLOCK_SIZE> output_bytes;

	while (input.peek() != EOF)
	{
		input.read(reinterpret_cast<char *>(input_bytes.data()), AES_BLOCK_SIZE);

		AES_decrypt(input_bytes.data(), output_bytes.data(), (const AES_KEY *)aes_key.get());

		output.write(reinterpret_cast<char *>(output_bytes.data()), input.gcount());

		std::uintmax_t new_percent = (current_chunk * 100) / total_chunks;
		if(current_percent != new_percent)
		{
			std::cout << "\rDecrypting... (" << (current_chunk * 100) / total_chunks << "%)" << std::flush;
			current_percent = new_percent;
		}
		current_chunk++;
	}

	std::cout << std::endl << "Decryption completed!" << std::endl;

	input.close();
	output.close();

	std::filesystem::remove(TMP_FILE);
}
