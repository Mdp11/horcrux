#include "args_parser.hpp"

#include <iostream>

args_parsing::ArgsParser::ArgsParser(int argc, char **argv)
{
	if (argc < 6)
	{
		throw ArgsException("wrong number of arguments");
	}
	std::vector<std::string> args(argv + 1, argv + argc);
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