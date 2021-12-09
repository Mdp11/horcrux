#include "args_parser.hpp"

#include <iostream>

args_parsing::ArgsParser::ArgsParser(int argc, char **argv)
{
	if (argc < 6)
	{
		throw ArgsException("wrong number of arguments");
	}

	std::vector<std::string> args(argv + 1, argv + argc);

	std::string &command = args.at(0);
	if (command != "create" && command != "load")
	{
		throw ArgsException("unknown command \"" + command + "\"");
	}
	command_ = std::move(command);

	if (command_ == "create")
	{
		std::string &option = args.at(1);
		if (option != "-n")
		{
			throw ArgsException("wrong option \"" + option + "\"");
		}

		try
		{
			n_horcruxes_ = std::stoi(args.at(2));
			if (n_horcruxes_ < MIN_HORCRUXES || n_horcruxes_ > MAX_HORCRUXES)
			{
				throw ArgsException(
					"horcrux_count must be a number in the range [" + std::to_string(MIN_HORCRUXES) + ","
						+ std::to_string(MAX_HORCRUXES) + "]");
			}

			input_file_ = std::move(args.at(3));
			output_folder_ = std::move(args.at(4));
		}
		catch (const std::invalid_argument &e)
		{
			throw ArgsException("horcrux_count must be a number in the range [" + std::to_string(MIN_HORCRUXES) + ","
									+ std::to_string(MAX_HORCRUXES) + "]");
		}
		catch (const std::out_of_range &e)
		{
			throw ArgsException("horcrux_count must be a number in the range [" + std::to_string(MIN_HORCRUXES) + ","
									+ std::to_string(MAX_HORCRUXES) + "]");
		}
	}
	else
	{
		std::string &option = args.at(1);
		if (option != "-k")
		{
			throw ArgsException("wrong option \"" + option + "\"");
		}

		decryption_key_ = std::move(args.at(2));

		for (auto it = args.begin() + 3; it != args.end() - 1; ++it)
		{
			horcruxes_paths_.push_back(std::move(*it));
		}

		output_file_ = std::move(args.back());
	}
}

void args_parsing::ArgsParser::printUsage()
{
	std::cout << "### Horcrux usage ###" << std::endl << std::endl;
	std::cout << "To split your file into horcruxes use the following command:" << std::endl;
	std::cout << "horcrux create -n <number_of_horcruxes> <input_file> <output_folder>" << std::endl;
	std::cout << std::endl;
	std::cout << "To merge horcruxes back into your file use the following command:" << std::endl;
	std::cout << "horcrux load -k <decryption_key> <input_file_1> ... <input_file_n> <output_file>" << std::endl;
}