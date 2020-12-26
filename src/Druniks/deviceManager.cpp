#include <iostream>
#include <vector>
#include "common.h"
#include "alc.h"

#include "deviceManager.h"

bool getAvailableDevices(std::vector<std::string>& devicesVec, ALCdevice* device)
{
	const ALCchar* devices;
	if (!alcCall(alcGetString, devices, device, nullptr, ALC_DEVICE_SPECIFIER))
		return false;

	const char* ptr = devices;

	devicesVec.clear();

	do
	{
		devicesVec.push_back(std::string(ptr));
		ptr += devicesVec.back().size() + 1;
	} while (*(ptr + 1) != '\0');

	return true;
}
