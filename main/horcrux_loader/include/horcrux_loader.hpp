#ifndef HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_HORCRUX_LOADER
#define HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_HORCRUX_LOADER

#include <string>
#include <vector>

#include "abstract_horcrux_loader.hpp"

namespace horcrux
{
class HorcruxLoader : public AbstractHorcruxLoader
{
public:
	HorcruxLoader(std::string decryption_key, std::vector<std::string> horcruxes_paths_, std::string output_file);

	void loadHorcruxes() override;

private:
	std::string decryption_key_;
	std::vector<std::string> horcruxes_paths_;
	std::string output_file_;

	void join() override;
	void decrypt() override;
	void store() override;
};
}


#endif //HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_HORCRUX_LOADER
