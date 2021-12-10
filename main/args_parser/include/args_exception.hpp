#ifndef HORCRUX_MAIN_ARGS_PARSER_ARGS_EXCEPTION_HPP
#define HORCRUX_MAIN_ARGS_PARSER_ARGS_EXCEPTION_HPP

#include <iostream>
#include <exception>
#include <string>

namespace args_parsing
{

class ArgsException: public std::exception
{
public:

	ArgsException(std::string message)
	{
		message_ = "ArgsException: " + message + ".";
	};

	const char *what() const throw()
	{
		return message_.c_str();
	}

private:
	std::string message_{};
};

}

#endif //HORCRUX_MAIN_ARGS_PARSER_ARGS_EXCEPTION_HPP
