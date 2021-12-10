#include <iostream>

#include "args_parser.hpp"
#include "horcrux_generator.hpp"

int main(int argc, char **argv)
{
	try
	{
		args_parsing::ArgsParser args_parser{argc, argv};

		if(args_parser.command == "create")
		{
			horcrux::HorcruxGenerator horcrux_generator{args_parser.n_horcruxes, std::move(args_parser.input_file), std::move(args_parser.output_folder)};
			horcrux_generator.createHorcruxes();
		}

	}
	catch (const args_parsing::ArgsException &e)
	{
		std::cout << e.what() << std::endl;
		args_parsing::ArgsParser::printUsage();
		return 1;
	}
}