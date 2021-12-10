#ifndef HORCRUX_MAIN_HORCRUX_GENERATOR_INCLUDE_HORCRUX_GENERATE_EXCEPTION_HPP
#define HORCRUX_MAIN_HORCRUX_GENERATOR_INCLUDE_HORCRUX_GENERATE_EXCEPTION_HPP

namespace horcrux
{

class HorcruxGenerateException: public std::exception
{
public:

	HorcruxGenerateException(std::string message)
	{
		message_ = "HorcruxGenerateException: " + message + ".";
	};

	const char *what() const throw()
	{
		return message_.c_str();
	}

private:
	std::string message_{};
};

}

#endif //HORCRUX_MAIN_HORCRUX_GENERATOR_INCLUDE_HORCRUX_GENERATE_EXCEPTION_HPP
