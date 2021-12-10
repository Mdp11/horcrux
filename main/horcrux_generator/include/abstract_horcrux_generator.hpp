#ifndef HORCRUX_MAIN_HORCRUX_INCLUDE_ABSTRACT_HORCRUX_GENERATOR
#define HORCRUX_MAIN_HORCRUX_INCLUDE_ABSTRACT_HORCRUX_GENERATOR

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
	virtual void store() = 0;
};
}

#endif //HORCRUX_MAIN_HORCRUX_INCLUDE_ABSTRACT_HORCRUX_GENERATOR
