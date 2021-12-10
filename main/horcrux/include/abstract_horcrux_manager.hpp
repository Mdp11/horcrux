#ifndef HORCRUX_MAIN_HORCRUX_ABSTRACT_HORCRUX_MANAGER
#define HORCRUX_MAIN_HORCRUX_ABSTRACT_HORCRUX_MANAGER

namespace horcrux
{
class AbstractHorcruxManager
{
public:
	AbstractHorcruxManager() = default;

	virtual void createHorcruxes() = 0;
	virtual void loadHorcruxes() = 0;

private:
	virtual void encrypt() = 0;
	virtual void decrypt() = 0;
	virtual void split() = 0;
	virtual void store() = 0;
	virtual void join() = 0;

};
}

#endif //HORCRUX_MAIN_HORCRUX_ABSTRACT_HORCRUX_MANAGER
