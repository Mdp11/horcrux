#include "horcrux_generator.hpp"

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <filesystem>
#include <algorithm>

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
	if (n_horcruxes_ < MIN_HORCRUXES || n_horcruxes_ > MAX_HORCRUXES)
	{
		throw HorcruxGenerateException("invalid number of horcruxes specified");
	}

	if (!std::filesystem::exists(input_file_))
	{
		throw HorcruxGenerateException(input_file_ + " does not exist");
	}

	if (std::filesystem::is_directory(input_file_))
	{
		throw HorcruxGenerateException(input_file_ + " is not a file");
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

	std::cout << "WARNING: store the following key with caution, you will need it to join your horcruxes back together:" << std::endl;
	std::cout << output_buffer.get() << std::endl;
}

void horcrux::HorcruxGenerator::encrypt()
{

	std::unique_ptr<AES_KEY> aes_key = std::make_unique<AES_KEY>();
	AES_set_encrypt_key(key_.data(), 256, aes_key.get());

	std::ifstream input(input_file_, std::ios::binary);

	if (input.fail())
	{
		throw HorcruxGenerateException("error opening " + input_file_);
	}

	std::ofstream output(TMP_FILE, std::ios::binary);
	if (output.fail())
	{
		throw HorcruxGenerateException("error creating temporary encrypted file");
	}

	std::uintmax_t file_size = std::filesystem::file_size(input_file_);
	std::uintmax_t total_chunks = file_size / AES_BLOCK_SIZE;
	std::uintmax_t current_chunk{1};
	std::uintmax_t current_percent{0};

	while (input.peek() != EOF)
	{
		std::array<unsigned char, AES_BLOCK_SIZE> input_bytes{0};
		std::array<unsigned char, AES_BLOCK_SIZE> output_bytes{0};

		input.read(reinterpret_cast<char *>(input_bytes.data()), AES_BLOCK_SIZE);

		if (input.gcount() < static_cast<long int>(AES_BLOCK_SIZE))
		{
			auto required_padding = AES_BLOCK_SIZE - input.gcount();

			for (std::size_t i = input_bytes.size() - required_padding; i < input_bytes.size(); ++i)
			{
				input_bytes.at(i) = required_padding;
			}
		}

		AES_encrypt(input_bytes.data(), output_bytes.data(), (const AES_KEY *)aes_key.get());

		output.write(reinterpret_cast<char *>(output_bytes.data()), AES_BLOCK_SIZE);


		std::uintmax_t new_percent = (current_chunk * 100) / total_chunks;
		if(current_percent != new_percent)
		{
			std::cout << "Encrypting... (" << (current_chunk * 100) / total_chunks << "%)" << std::endl;
			current_percent = new_percent;
		}
		current_chunk++;
	}

	std::cout << "Encryption completed!" << std::endl;

	input.close();
	output.close();

}

void horcrux::HorcruxGenerator::split()
{
	std::uintmax_t file_size = std::filesystem::file_size(TMP_FILE);
	std::uintmax_t horcrux_size = file_size / n_horcruxes_;
	std::uintmax_t horcrux_remainder_size = file_size % n_horcruxes_;

	std::ifstream encrypted_file{TMP_FILE, std::ios::binary};
	if (encrypted_file.fail())
	{
		std::filesystem::remove(TMP_FILE);
		throw HorcruxGenerateException("error opening generated encrypted file");
	}

	std::filesystem::create_directories(output_folder_);

	std::array<char, MAX_RW_BYTES> buffer{};
	std::uintmax_t rw_size = std::min(horcrux_size, MAX_RW_BYTES);

	int i{0};

	for (; i < n_horcruxes_; ++i)
	{
		std::cout << "Generating horcrux " << i + 1 << "/" << n_horcruxes_ << "..." << std::endl;

		std::ofstream horcrux_output{output_folder_ + "/horcrux_" + std::to_string(i), std::ios::binary};
		if (horcrux_output.fail())
		{
			std::filesystem::remove(TMP_FILE);
			throw HorcruxGenerateException("error creating horcrux file");
		}

		for (unsigned int j = 0; j < horcrux_size / rw_size; ++j)
		{
			encrypted_file.read(buffer.data(), rw_size);
			horcrux_output.write(buffer.data(), encrypted_file.gcount());
		}

		if (horcrux_size % rw_size != 0)
		{
			encrypted_file.read(buffer.data(), horcrux_size % rw_size);
			horcrux_output.write(buffer.data(), encrypted_file.gcount());
		}

		if (i + 1 == n_horcruxes_ && horcrux_remainder_size != 0)
		{
			rw_size = std::min(horcrux_remainder_size, MAX_RW_BYTES);

			for (unsigned int j = 0; j < horcrux_remainder_size / rw_size; ++j)
			{
				encrypted_file.read(buffer.data(), rw_size);
				horcrux_output.write(buffer.data(), encrypted_file.gcount());
			}
			if (horcrux_remainder_size % rw_size != 0)
			{
				encrypted_file.read(buffer.data(), horcrux_remainder_size % rw_size);
				horcrux_output.write(buffer.data(), encrypted_file.gcount());
			}
		}

		horcrux_output.close();
	}

	std::cout << "Horcrux generation completed!" << std::endl;

	encrypted_file.close();
	std::filesystem::remove(TMP_FILE);
}
