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
	std::cout << "USAGE" << std::endl;
}