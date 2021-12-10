#include "horcrux_loader.hpp"

#include <memory>
#include <fstream>
#include <vector>

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
	decodeKey();
	decrypt();
}

void horcrux::HorcruxLoader::decodeKey()
{
	const auto predicted_length = 3 * decoded_key_.size() / 4;
	auto decoded_key = reinterpret_cast<unsigned char *>(calloc(predicted_length + 1, 1));
	const auto output_length = EVP_DecodeBlock(decoded_key, reinterpret_cast<const unsigned char *>(decryption_key_.data()), decoded_key_.size());
	if (predicted_length != output_length)
	{
		throw HorcruxLoadException("error decoding key from base64");
	}

	for(int i = 0; i < output_length; ++i)
	{
		decoded_key_.at(i) = decoded_key[i];
	}
}

void horcrux::HorcruxLoader::join()
{}

void horcrux::HorcruxLoader::decrypt()
{
	std::unique_ptr<AES_KEY> aes_key = std::make_unique<AES_KEY>();
	AES_set_decrypt_key(decoded_key_.data(), 256, aes_key.get());

	std::ifstream input("tmp", std::ios::binary);
	std::ofstream output(output_file_, std::ios::binary); //TODO: check output file does not exist

	std::array<unsigned char, AES_BLOCK_SIZE> input_bytes;
	std::array<unsigned char, AES_BLOCK_SIZE> output_bytes;

	while (input.peek() != EOF)
	{
		input.read(reinterpret_cast<char *>(input_bytes.data()), AES_BLOCK_SIZE);

		std::vector<unsigned char> in(input.gcount());
		std::vector<unsigned char> out(input.gcount());

		std::copy(input_bytes.begin(), input_bytes.begin() + input.gcount(), in.begin());

		AES_decrypt(in.data(), out.data(), (const AES_KEY *)aes_key.get());

		output.write(reinterpret_cast<char *>(output_bytes.data()), input.gcount());
	}

	input.close();
	output.close();
}

void horcrux::HorcruxLoader::store()
{}
