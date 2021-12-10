#include "horcrux_generator.hpp"

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>

#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

#include "horcrux_generate_exception.hpp"

horcrux::HorcruxGenerator::HorcruxGenerator(int n_horcruxes, std::string input_file, std::string output_folder)
	: n_horcruxes_{n_horcruxes}, input_file_{std::move(input_file)}, output_folder_{std::move(output_folder)}
{}

void horcrux::HorcruxGenerator::createHorcruxes()
{
	generateKey();
	encrypt();
	printKey();
}

void horcrux::HorcruxGenerator::generateKey()
{
	if (RAND_bytes(key_.data(), key_.size()) != 1)
	{
		throw HorcruxGenerateException("openssl RAND_bytes failed with code " + std::to_string(ERR_get_error()));
	}
}

void horcrux::HorcruxGenerator::printKey()
{
//	const auto predicted_length = 4 * ((KEY_SIZE + 2) / 3);
//	auto encoded_key = reinterpret_cast<char *>(calloc(predicted_length + 1, 1));
//	const auto output_length = EVP_EncodeBlock(reinterpret_cast<unsigned char *>(encoded_key), key_.data(), KEY_SIZE);
//	if (predicted_length != output_length)
//	{
//		throw HorcruxGenerateException("error encoding the key in base64");
//	}
//
//	std::cout << encoded_key << std::endl;


	const auto predicted_length = 4 * ((KEY_SIZE + 2) / 3);

	const auto output_buffer{std::make_unique<char[]>(predicted_length + 1)};

	const std::vector<unsigned char> chars{key_.begin(), key_.end()};

	const auto output_length = EVP_EncodeBlock(reinterpret_cast<unsigned char *>(output_buffer.get()),
											   chars.data(),
											   static_cast<int>(chars.size()));

	if (predicted_length != static_cast<unsigned long>(output_length))
	{
		throw HorcruxGenerateException("error encoding the key in base64");
	}

	std::cout << output_buffer.get() << std::endl;
}

void horcrux::HorcruxGenerator::encrypt()
{
	std::unique_ptr<AES_KEY> aes_key = std::make_unique<AES_KEY>();
	AES_set_encrypt_key(key_.data(), 256, aes_key.get());

	std::ifstream input(input_file_, std::ios::binary); //TODO: check input file exists and is a file
	std::ofstream output("tmp", std::ios::binary);

	std::array<unsigned char, AES_BLOCK_SIZE> input_bytes;

	while (input.peek() != EOF)
	{
		input.read(reinterpret_cast<char *>(input_bytes.data()), AES_BLOCK_SIZE);

		std::vector<unsigned char> in(input.gcount());
		std::vector<unsigned char> out(input.gcount());

		std::copy(input_bytes.begin(), input_bytes.begin() + input.gcount(), in.begin());

		AES_encrypt(in.data(), out.data(), (const AES_KEY *)aes_key.get());

		output.write(reinterpret_cast<char *>(out.data()), input.gcount());
	}

	input.close();
	output.close();
}

void horcrux::HorcruxGenerator::split()
{}

void horcrux::HorcruxGenerator::store()
{}
