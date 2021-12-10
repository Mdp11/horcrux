#include "horcrux_generator.hpp"

horcrux::HorcruxGenerator::HorcruxGenerator(int n_horcruxes, std::string input_file, std::string output_folder)
	: n_horcruxes_{n_horcruxes}, input_file_{std::move(input_file)}, output_folder_{std::move(output_folder)}
{}

void horcrux::HorcruxGenerator::createHorcruxes()
{}

void horcrux::HorcruxGenerator::generateKey()
{}

void horcrux::HorcruxGenerator::encrypt()
{}

void horcrux::HorcruxGenerator::split()
{}

void horcrux::HorcruxGenerator::store()
{}
