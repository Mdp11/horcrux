#ifndef HORCRUX_MAIN_ARGS_PARSER_ARGSPARSER_H
#define HORCRUX_MAIN_ARGS_PARSER_ARGSPARSER_H

#include <string>
#include <vector>

#include "args_exception.h"

namespace args_parsing
{

class ArgsParser
{
public:
	ArgsParser(int argc, char** argv);

	static void printUsage();

private:
	std::string command_;

	std::string input_file_;
	std::string output_folder_;

	std::vector<std::string> horcruxes_paths_;
	std::string output_file;
};

}

#endif //HORCRUX_MAIN_ARGS_PARSER_ARGSPARSER_H
