#include <iostream>
#include <vector>
#include "common.h"
#include "wav.h"
#include "al.h"
#include "alc.h"

int main()
{
	ALCdevice* openALDevice = alcOpenDevice(nullptr);
	if (!openALDevice)
		return 0;

	ALCcontext* openALContext;
	if (!alcCall(alcCreateContext, openALContext, openALDevice, openALDevice, nullptr) || !openALContext)
	{
		std::cerr << "ERROR: Could not create audio context" << std::endl;
		return 0;
	}

	ALCboolean contextMadeCurrent = false;
	if (!alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, openALContext) || contextMadeCurrent != ALC_TRUE)
	{
		std::cerr << "ERROR: Could not make audio context current" << std::endl;
		return 0;
	}

	std::uint8_t channels;
	std::int32_t sampleRate;
	std::uint8_t bitsPerSample;
	std::vector<char> soundData;
	if (!load_wav("iamtheprotectorofthissystem.wav", channels, sampleRate, bitsPerSample, soundData))
	{
		std::cerr << "ERROR: Could not load wav" << std::endl;
		return 0;
	}

	ALuint buffer;
	alCall(alGenBuffers, 1, &buffer);

	ALenum format;
	if (channels == 1 && bitsPerSample == 8)
		format = AL_FORMAT_MONO8;
	else if (channels == 1 && bitsPerSample == 16)
		format = AL_FORMAT_MONO16;
	else if (channels == 2 && bitsPerSample == 8)
		format = AL_FORMAT_STEREO8;
	else if (channels == 2 && bitsPerSample == 16)
		format = AL_FORMAT_STEREO16;
	else
	{
		std::cerr
			<< "ERROR: unrecognised wave format: "
			<< channels << " channels, "
			<< bitsPerSample << " bps" << std::endl;
		return 0;
	}

	alCall(alBufferData, buffer, format, soundData.data(), soundData.size(), sampleRate);
	soundData.clear(); // erase the sound in RAM

	ALuint source;
	alCall(alGenSources, 1, &source);
	alCall(alSourcef, source, AL_PITCH, 1);
	alCall(alSourcef, source, AL_GAIN, 1.0f);
	alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
	alCall(alSource3f, source, AL_VELOCITY, 0, 0, 0);
	alCall(alSourcei, source, AL_LOOPING, AL_FALSE);
	alCall(alSourcei, source, AL_BUFFER, buffer);

	alCall(alSourcePlay, source);

	ALint state = AL_PLAYING;

	while (state == AL_PLAYING)
	{
		alCall(alGetSourcei, source, AL_SOURCE_STATE, &state);
	}

	alCall(alDeleteSources, 1, &source);
	alCall(alDeleteBuffers, 1, &buffer);

	alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
	alcCall(alcDestroyContext, openALDevice, openALContext);

	ALCboolean closed;
	alcCall(alcCloseDevice, closed, openALDevice, openALDevice);

	return 0;
}