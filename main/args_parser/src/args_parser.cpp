#include "args_parser.hpp"

#include <iostream>

#include "constants.hpp"

args_parsing::ArgsParser::ArgsParser(int argc, char **argv)
{
	if (argc < 6)
	{
		throw ArgsException("too few arguments");
	}

	std::vector<std::string> args(argv + 1, argv + argc);

	std::string &input_command = args.at(0);
	if (input_command != "create" && input_command != "load")
	{
		throw ArgsException("unknown command \"" + command + "\"");
	}
	command = std::move(input_command);

	if (command == "create")
	{
		if(argc > 6)
		{
			throw ArgsException("too many arguments");
		}
		std::string &option = args.at(1);
		if (option != "-n")
		{
			throw ArgsException("wrong option \"" + option + "\"");
		}

		try
		{
			n_horcruxes = std::stoi(args.at(2));
			if (n_horcruxes < horcrux::MIN_HORCRUXES || n_horcruxes > horcrux::MAX_HORCRUXES)
			{
				throw ArgsException(
					"horcrux_count must be a number in the range [" + std::to_string(horcrux::MIN_HORCRUXES) + ","
						+ std::to_string(horcrux::MAX_HORCRUXES) + "]");
			}

			input_file = std::move(args.at(3));
			output_folder = std::move(args.at(4));
		}
		catch (const std::invalid_argument &e)
		{
			throw ArgsException("horcrux_count must be a number in the range [" + std::to_string(horcrux::MIN_HORCRUXES) + ","
									+ std::to_string(horcrux::MAX_HORCRUXES) + "]");
		}
		catch (const std::out_of_range &e)
		{
			throw ArgsException("horcrux_count must be a number in the range [" + std::to_string(horcrux::MIN_HORCRUXES) + ","
									+ std::to_string(horcrux::MAX_HORCRUXES) + "]");
		}
	}
	else
	{
		std::string &option = args.at(1);
		if (option != "-k")
		{
			throw ArgsException("wrong option \"" + option + "\"");
		}

		decryption_key = std::move(args.at(2));

		for (auto it = args.begin() + 3; it != args.end() - 1; ++it)
		{
			horcruxes_paths.push_back(std::move(*it));
		}

		output_file = std::move(args.back());
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