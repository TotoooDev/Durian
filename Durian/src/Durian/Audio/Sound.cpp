#include <pch.h>
#include <Durian/Audio/Sound.h>
#include <AL/al.h>
#include <sndfile.h>

#include <Durian/Core/OS.h>
#ifndef DURIAN_WINDOWS // I'm too lazy to implement this for Windows
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#endif
#define MINIMP3_IMPLEMENTATION
#include <minimp3.h>
#include <minimp3_ex.h>

namespace Durian
{
	Sound::Sound(const std::string& path)
	{
        std::string extension = path.substr(path.find_last_of(".") + 1);
        if (extension == "mp3")
            LoadMP3(path);
        else if (extension == "ogg")
            LoadOGG(path);
        else
            LoadOther(path);
	}

	Sound::~Sound()
	{
		alDeleteBuffers(1, &m_ID);
	}

    void Sound::LoadMP3(const std::string& path)
    {
        mp3dec_t decoder;
        mp3dec_file_info_t info;
        if (mp3dec_load(&decoder, path.c_str(), &info, nullptr, nullptr))
        {
            DURIAN_LOG_ERROR("Failed to load {}!", path);
            return;
        }

        ALenum format;
        switch (info.channels)
        {
        case 1:
            format = AL_FORMAT_MONO16;
            break;
        case 2:
            format = AL_FORMAT_STEREO16;
            break;
        default:
            DURIAN_LOG_ERROR("Unknown format!");
            break;
        }

        alGenBuffers(1, &m_ID);
        alBufferData(m_ID, format, info.buffer, info.samples * sizeof(mp3d_sample_t), info.hz);

        free(info.buffer);
    }

    void Sound::LoadOGG(const std::string& path)
    {
        DURIAN_LOG_ERROR("OGG format is not supported!");
    } 

    void Sound::LoadOther(const std::string& path)
    {
        SF_INFO fileInfo;
        SNDFILE* file = sf_open(path.c_str(), SFM_READ, &fileInfo);
        if (!file)
        {
            DURIAN_LOG_ERROR("Failed to load {}!", path);
            DURIAN_LOG_ERROR(sf_strerror(file));
            return;
        }

        unsigned int numSamples = fileInfo.channels * fileInfo.frames;
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
}
