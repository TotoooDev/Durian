#include <pch.h>
#include <Durian/Audio/Sound.h>
#include <AL/al.h>
#include <sndfile.h>

namespace Durian
{
	Sound::Sound(const std::string& path)
	{
		SF_INFO fileInfo;
		SNDFILE* file = sf_open(path.c_str(), SFM_READ, &fileInfo);
		if (!file)
		{
			DURIAN_LOG_ERROR("Failed to load {}!", path);
			DURIAN_LOG_ERROR(sf_strerror(file));
			return;
		}

		unsigned int numSamples = fileInfo.samplerate * fileInfo.frames;
		unsigned int sampleRate = fileInfo.samplerate;

		std::vector<short> samples(numSamples);
		if (sf_read_short(file, samples.data(), numSamples) < numSamples)
		{
			DURIAN_LOG_ERROR(sf_strerror(file));
			return;
		}

		sf_close(file);

		ALenum format;
		switch (fileInfo.channels)
		{
		case 1:
			format = AL_FORMAT_MONO16;
			break;
		case 2:
			format = AL_FORMAT_STEREO16;
			break;
		default:
			DURIAN_LOG_ERROR("Unknown format!");
			return;
		}

		alGenBuffers(1, &m_ID);
		alBufferData(m_ID, format, samples.data(), numSamples * sizeof(short), sampleRate);
	}

	Sound::~Sound()
	{
		alDeleteBuffers(1, &m_ID);
	}
}