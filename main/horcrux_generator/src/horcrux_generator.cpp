#include "horcrux_generator.hpp"

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <filesystem>

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
	checkInputs();
	generateKey();
	encrypt();
	split();
	printKey();
}

void horcrux::HorcruxGenerator::checkInputs()
{
	if(n_horcruxes_ < MIN_HORCRUXES || n_horcruxes_ > MAX_HORCRUXES)
	{
		throw HorcruxGenerateException("invalid number of horcruxes specified");
	}

	if(!std::filesystem::exists(input_file_))
	{
		throw HorcruxGenerateException(input_file_ + "does not exist");
	}

	if(std::filesystem::is_directory(input_file_))
	{
		throw HorcruxGenerateException(input_file_ + "is not a file");
	}

	if(!std::filesystem::exists(output_folder_))
	{
		throw HorcruxGenerateException(output_folder_ + "does not exist");
	}

	if(!std::filesystem::is_directory(output_folder_))
	{
		throw HorcruxGenerateException(output_folder_ + "is not a directory");
	}
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

	std::ifstream input(input_file_, std::ios::binary);

	if(input.fail())
	{
		throw HorcruxGenerateException("error opening " + input_file_);
	}

	std::ofstream output("tmp", std::ios::binary);
	if(output.fail())
	{
		throw HorcruxGenerateException("error creating temporary encrypted file");
	}

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
{
	std::uintmax_t file_size = std::filesystem::file_size("tmp");

	std::uintmax_t horcrux_size = file_size / n_horcruxes_;
	std::uintmax_t horcrux_remainder_size = file_size % n_horcruxes_;

	std::unique_ptr<char[]> buffer = std::make_unique<char[]>(horcrux_size);

	std::ifstream encrypted_file{"tmp", std::ios::binary};
	if(encrypted_file.fail())
	{
		std::filesystem::remove("tmp");
		throw HorcruxGenerateException("error opening generated encrypted file");
	}

	std::filesystem::create_directories(output_folder_);

	for (int i = 0; i < n_horcruxes_; ++i)
	{
		std::ofstream horcrux_output{output_folder_ + "/horcrux_" + std::to_string(i), std::ios::binary};
		if(horcrux_output.fail())
		{
			std::filesystem::remove("tmp");
			throw HorcruxGenerateException("error creating horcrux file");
		}
		if(i == 0)
		{
			encrypted_file.read(buffer.get(), horcrux_size + horcrux_remainder_size);
		}
		else
		{
			encrypted_file.read(buffer.get(), horcrux_size);
		}
		horcrux_output.write(buffer.get(), encrypted_file.gcount());
		horcrux_output.close();
	}

	encrypted_file.close();
	std::filesystem::remove("tmp");
}
