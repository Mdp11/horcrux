#ifndef HORCRUX_MAIN_UTILS_INCLUDE_CONSTANTS_HPP
#define HORCRUX_MAIN_UTILS_INCLUDE_CONSTANTS_HPP

#include <string>

namespace horcrux
{
constexpr int MIN_HORCRUXES{1};

constexpr int MAX_HORCRUXES{1000};

const std::string TMP_FILE{"tmp"};

constexpr std::uintmax_t MAX_RW_BYTES{1024};

constexpr uint8_t KEY_SIZE{32};
}

#endif //HORCRUX_MAIN_UTILS_INCLUDE_CONSTANTS_HPP
