#include <pch.h>
#include <Durian/Audio/Sound.h>
#include <AL/al.h>
#include <sndfile.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

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
        DURIAN_LOG_WARN("MP3 format is not supported yet!");
    }

    void Sound::LoadOGG(const std::string& path)
    {        
        // Shamelessly stolen from https://xiph.org/vorbis/doc/vorbisfile/example.html
        char pcmout[4096];

        OggVorbis_File vf;
        int eof = 0;
        int currentSection;

        if (ov_fopen(path.c_str(), &vf) < 0)
        {
            DURIAN_LOG_WARN("{} is not an OGG bitstream!", path);
            // LoadNotMP3(path);
        }
        
        // Print cool informations
        char** ptr = ov_comment(&vf, -1)->user_comments;
        vorbis_info* vi = ov_info(&vf, -1);
        while (*ptr)
        {
            DURIAN_LOG_INFO(*ptr);
            ++ptr;
        }
        DURIAN_LOG_INFO("Bitstream is {0} channel, {1}hz", vi->channels, vi->rate);
        DURIAN_LOG_INFO("Decoded length: {} samples", ov_pcm_total(&vf, -1));
        DURIAN_LOG_INFO("Encoded by {}", ov_comment(&vf, -1)->vendor);
    
        while (!eof)
        {
            long ret = ov_read(&vf, pcmout, sizeof(pcmout), 0, 2, 1, &currentSection);
            if (ret == 0)
                eof = 1; // End of file
            else if (ret < 0)
                DURIAN_LOG_ERROR("Error in the stream!");
            else
                DURIAN_LOG_INFO("so apparently i have to do something here but the example doesn't tell me what it is :(");
        }

        ov_clear(&vf);
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
