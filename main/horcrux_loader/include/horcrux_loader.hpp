#ifndef HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_HORCRUX_LOADER_HPP
#define HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_HORCRUX_LOADER_HPP

#include <string>
#include <vector>
#include <array>

#include "abstract_horcrux_loader.hpp"
#include "constants.hpp"

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

	std::array<uint8_t, KEY_SIZE> decoded_key_;

	void checkInputs();
	void decodeKey();
	void join() override;
	void decrypt() override;
};
}


#endif //HORCRUX_MAIN_HORCRUX_LOADER_INCLUDE_HORCRUX_LOADER_HPP
