#ifndef HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_ABSTRACT_HORCRUX_LOADER_HPP
#define HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_ABSTRACT_HORCRUX_LOADER_HPP

namespace horcrux
{
class AbstractHorcruxLoader
{
public:
	AbstractHorcruxLoader() = default;

	virtual void loadHorcruxes() = 0;

private:
	virtual void join() = 0;
	virtual void decrypt() = 0;
};
}

#endif //HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_ABSTRACT_HORCRUX_LOADER_HPP
