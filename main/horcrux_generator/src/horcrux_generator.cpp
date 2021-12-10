#include "horcrux_generator.hpp"

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>

#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/aes.h>


#include "horcrux_generate_exception.hpp"

horcrux::HorcruxGenerator::HorcruxGenerator(int n_horcruxes, std::string input_file, std::string output_folder)
	: n_horcruxes_{n_horcruxes}, input_file_{std::move(input_file)}, output_folder_{std::move(output_folder)}
{}

void horcrux::HorcruxGenerator::createHorcruxes()
{
	generateKey();
	encrypt();
}

void horcrux::HorcruxGenerator::generateKey()
{
	if (RAND_bytes(key_.data(), key_.size()) != 1)
	{
		throw HorcruxGenerateException("openssl RAND_bytes failed with code " + std::to_string(ERR_get_error()));
	}
}

void horcrux::HorcruxGenerator::encrypt()
{
	std::unique_ptr<AES_KEY> aes_key = std::make_unique<AES_KEY>();
	AES_set_encrypt_key(key_.data(), 256, aes_key.get());

	std::ifstream input(input_file_, std::ios::binary); //TODO: check input file exists and is a file
	std::ofstream output("tmp", std::ios::binary);

	std::array<unsigned char, AES_BLOCK_SIZE> input_bytes;
	std::array<unsigned char, AES_BLOCK_SIZE> output_bytes;

	while (input.peek() != EOF)
	{
		input.read(reinterpret_cast<char*>(input_bytes.data()), AES_BLOCK_SIZE);

		std::vector<unsigned char> in(input.gcount());
		std::vector<unsigned char> out(input.gcount());

		std::copy(input_bytes.begin(), input_bytes.begin() + input.gcount(), in.begin());

		AES_encrypt(in.data(), out.data(), (const AES_KEY *)aes_key.get());

		output.write(reinterpret_cast<char*>(output_bytes.data()), input.gcount());
	}

	input.close();
	output.close();
}

void horcrux::HorcruxGenerator::split()
{}

void horcrux::HorcruxGenerator::store()
{}
