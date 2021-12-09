#include <gtest/gtest.h>

#include "../args_parser.hpp"

TEST(ArgsParser, VALID_CREATE)
{
	bool exception_thrown{false};

	std::vector<std::string> arguments {"horcrux", "create", "-n", "10", "/home/input_file.txt", "/home/output_folder"};
	std::vector<char*> argv;
	argv.reserve(arguments.size());

	for(size_t i = 0; i < arguments.size(); ++i)
	{
		argv.push_back(const_cast<char*>(arguments[i].c_str()));
	}

	try
	{
		args_parsing::ArgsParser args_parser(argv.size(), &argv[0]);
	}
	catch(const args_parsing::ArgsException& e)
	{
		exception_thrown = true;
	}

	EXPECT_FALSE(exception_thrown);
}

TEST(ArgsParser, VALID_LOAD_ONE_HORCRUX)
{
bool exception_thrown{false};

std::vector<std::string> arguments {"horcrux", "load", "-k", "asdasdqwe", "/home/horcrux1", "/home/output_folder"};
std::vector<char*> argv;
argv.reserve(arguments.size());

for(size_t i = 0; i < arguments.size(); ++i)
{
argv.push_back(const_cast<char*>(arguments[i].c_str()));
}

try
{
args_parsing::ArgsParser args_parser(argv.size(), &argv[0]);
}
catch(const args_parsing::ArgsException& e)
{
exception_thrown = true;
}

EXPECT_FALSE(exception_thrown);
}

TEST(ArgsParser, VALID_LOAD_MULTIPLE_HORCRUXES)
{
	bool exception_thrown{false};

	std::vector<std::string> arguments {"horcrux", "load", "-k", "asdasdqwe", "/home/horcrux1", "/home/horcrux2", "/home/horcrux3", "/home/output_folder"};
	std::vector<char*> argv;
	argv.reserve(arguments.size());

	for(size_t i = 0; i < arguments.size(); ++i)
	{
		argv.push_back(const_cast<char*>(arguments[i].c_str()));
	}

	try
	{
		args_parsing::ArgsParser args_parser(argv.size(), &argv[0]);
	}
	catch(const args_parsing::ArgsException& e)
	{
		exception_thrown = true;
	}

	EXPECT_FALSE(exception_thrown);
}