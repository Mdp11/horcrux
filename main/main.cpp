#include <iostream>

#include "args_parser/args_parser.hpp"

int main(int argc, char **argv)
{
	try
	{
		args_parsing::ArgsParser args_parser{argc, argv};
	}
	catch (const args_parsing::ArgsException &e)
	{
		std::cout << e.what() << std::endl;
		args_parsing::ArgsParser::printUsage();
		return 1;
	}
}