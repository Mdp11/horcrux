#ifndef HORCRUX_MAIN_HORCRUX_GENERATOR_INCLUDE_ABSTRACT_HORCRUX_GENERATOR_HPP
#define HORCRUX_MAIN_HORCRUX_GENERATOR_INCLUDE_ABSTRACT_HORCRUX_GENERATOR_HPP

namespace horcrux
{
class AbstractHorcruxGenerator
{
public:
	AbstractHorcruxGenerator() = default;

	virtual void createHorcruxes() = 0;

private:
	virtual void generateKey() = 0;
	virtual void encrypt() = 0;
	virtual void split() = 0;
};
}

#endif //HORCRUX_MAIN_HORCRUX_GENERATOR_INCLUDE_ABSTRACT_HORCRUX_GENERATOR_HPP
