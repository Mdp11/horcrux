#ifndef HORCRUX_MAIN_HORCRUX_INCLUDE_ABSTRACT_HORCRUX_LOADER
#define HORCRUX_MAIN_HORCRUX_INCLUDE_ABSTRACT_HORCRUX_LOADER

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
	virtual void store() = 0;
};
}

#endif //HORCRUX_MAIN_HORCRUX_INCLUDE_ABSTRACT_HORCRUX_LOADER
