#pragma once

#include <iostream>
#include "alc.h"

bool checkAlErrors(const std::string& filename, const std::uint_fast32_t line);
bool checkAlcErrors(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device);

