#include "horcrux_loader.hpp"

horcrux::HorcruxLoader::HorcruxLoader(std::string decryption_key,
									  std::vector<std::string> horcruxes_paths,
									  std::string output_file)
	: decryption_key_{std::move(decryption_key)}, horcruxes_paths_{std::move(horcruxes_paths)},
	  output_file_{std::move(output_file)}
{}

void horcrux::HorcruxLoader::loadHorcruxes()
{}

void horcrux::HorcruxLoader::join()
{}

void horcrux::HorcruxLoader::decrypt()
{}

void horcrux::HorcruxLoader::store()
{}
