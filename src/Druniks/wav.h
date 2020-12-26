#pragma once

#include <iostream>
#include <vector>

bool load_wav(
	const std::string& filename,
	std::uint8_t& channels,
	std::int32_t& sampleRate,
	std::uint8_t& bitsPerSample,
	std::vector<char> data);