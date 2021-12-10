#include <gtest/gtest.h>

#include "args_parser.hpp"

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


TEST(ArgsParser, INVALID_FEW_ARGUMENTS)
{
	bool exception_thrown{false};

	std::vector<std::string> arguments {"horcrux", "load", "-k", "asdasdqwe"};
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

	EXPECT_TRUE(exception_thrown);
}

TEST(ArgsParser, INVALID_UNKNOWN_COMMAND)
{
	bool exception_thrown{false};

	std::vector<std::string> arguments {"horcrux", "host", "-n", "10", "/home/input_file.txt", "/home/output_folder"};
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

	EXPECT_TRUE(exception_thrown);
}

TEST(ArgsParser, INVALID_CREATE_TOO_MANY_ARGUMENTS)
{
	bool exception_thrown{false};

std::vector<std::string> arguments {"horcrux", "create", "-n", "10", "/home/input_file.txt", "/home/output_folder", "exceeding_arg"};
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

	EXPECT_TRUE(exception_thrown);
}

TEST(ArgsParser, INVALID_CREATE_WRONG_OPTION)
{
	bool exception_thrown{false};

std::vector<std::string> arguments {"horcrux", "create", "-p", "10", "/home/input_file.txt", "/home/output_folder"};
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

	EXPECT_TRUE(exception_thrown);
}

TEST(ArgsParser, INVALID_LOAD_WRONG_OPTION)
{
	bool exception_thrown{false};

std::vector<std::string> arguments {"horcrux", "load", "-p", "asdasdqwe", "/home/horcrux1", "/home/horcrux2", "/home/horcrux3", "/home/output_folder"};
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

	EXPECT_TRUE(exception_thrown);
}

TEST(ArgsParser, INVALID_HORCRUX_COUNT_OUT_OF_RANGE)
{
	bool exception_thrown{false};

	std::vector<std::string> arguments {"horcrux", "create", "-n", "9999999999", "/home/input_file.txt", "/home/output_folder"};
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

	EXPECT_TRUE(exception_thrown);
}

TEST(ArgsParser, INVALID_HORCRUX_COUNT_LESSER_THAN_MIN)
{
	bool exception_thrown{false};

	std::vector<std::string> arguments {"horcrux", "create", "-n", std::to_string(args_parsing::MIN_HORCRUXES - 1), "/home/input_file.txt", "/home/output_folder"};
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

	EXPECT_TRUE(exception_thrown);
}

TEST(ArgsParser, INVALID_HORCRUX_COUNT_GREATER_THAN_MAX)
{
	bool exception_thrown{false};

	std::vector<std::string> arguments {"horcrux", "create", "-n", std::to_string(args_parsing::MAX_HORCRUXES + 1), "/home/input_file.txt", "/home/output_folder"};
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

	EXPECT_TRUE(exception_thrown);
}

