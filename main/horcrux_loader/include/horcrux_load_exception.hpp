#ifndef HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_HORCRUX_LOAD_EXCEPTION_HPP
#define HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_HORCRUX_LOAD_EXCEPTION_HPP

namespace horcrux
{

class HorcruxLoadException: public std::exception
{
public:

	HorcruxLoadException(std::string message)
	{
		message_ = "HorcruxLoadException: " + message + ".";
	};

	const char *what() const throw()
	{
		return message_.c_str();
	}

private:
	std::string message_{};
};

}

#endif //HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_HORCRUX_LOAD_EXCEPTION_HPP
