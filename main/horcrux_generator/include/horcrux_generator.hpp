#ifndef HORCRUX_MAIN_HORCRUX_GENERATOR_INCLUDE_HORCRUX_GENERATOR_HPP
#define HORCRUX_MAIN_HORCRUX_GENERATOR_INCLUDE_HORCRUX_GENERATOR_HPP

#include <array>
#include <string>

#include "abstract_horcrux_generator.hpp"
#include "constants.hpp"

namespace horcrux
{

class HorcruxGenerator : public AbstractHorcruxGenerator
{
public:
	HorcruxGenerator(int n_horcruxes, std::string input_file, std::string output_folder);

	void createHorcruxes() override;

private:

	int n_horcruxes_;
	std::string input_file_;
	std::string output_folder_;

	std::array<uint8_t, KEY_SIZE> key_;

	void generateKey() override;
	void printKey();
	void encrypt() override;
	void split() override;
	void store() override;
};
}


#endif //HORCRUX_MAIN_HORCRUX_GENERATOR_INCLUDE_HORCRUX_GENERATOR_HPP
