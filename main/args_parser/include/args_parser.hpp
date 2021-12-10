#ifndef HORCRUX_MAIN_ARGS_PARSER_INCLUDE_ARGS_PARSER_HPP
#define HORCRUX_MAIN_ARGS_PARSER_INCLUDE_ARGS_PARSER_HPP

#include <string>
#include <vector>

#include "args_exception.hpp"

namespace args_parsing
{

struct ArgsParser
{
	ArgsParser(int argc, char** argv);

	static void printUsage();

	std::string command{};

	int n_horcruxes{};
	std::string input_file{};
	std::string output_folder{};

	std::string decryption_key{};
	std::vector<std::string> horcruxes_paths{};
	std::string output_file{};
};

}

#endif //HORCRUX_MAIN_ARGS_PARSER_INCLUDE_ARGS_PARSER_HPP
