#include <pch.h>
#include <Durian/Audio/AudioEngine.h>
#include <AL/al.h>

namespace Durian
{
	AudioEngine::AudioEngine()
	{
		m_Device = alcOpenDevice(nullptr);
		if (!m_Device)
		{
			DURIAN_LOG_ERROR("Failed to open audio device!");
			return;
		}

		m_Context = alcCreateContext(m_Device, nullptr);
		alcMakeContextCurrent(m_Context); 
    }

	AudioEngine::~AudioEngine()
	{
		alcDestroyContext(m_Context);
		alcCloseDevice(m_Device);
	}

	void AudioEngine::PlaySound(Ref<Sound> sound)
	{
		if (!sound->m_Registered)
		{
			unsigned int source;
			alGenSources(1, &source);
			alSourcei(source, AL_BUFFER, sound->GetID());

			m_Sources[sound] = source;
			sound->m_Registered = true;

			alSourcePlay(source);
		}
		else
		{
			alSourcePlay(m_Sources[sound]);
		}
	}

	void AudioEngine::StopSound(Ref<Sound> sound)
	{
		alSourceStop(m_Sources[sound]);
	}

	bool AudioEngine::IsPlaying()
	{
		for (auto const& x : m_Sources)
		{
			int status;
			alGetSourcei(x.second, AL_SOURCE_STATE, &status);
			if (status == AL_PLAYING)
				return true;
		}
		return false;
	}

	void AudioEngine::PrintErrors()
	{
		ALenum error;
		while ((error = alGetError()) != AL_NO_ERROR)
		{
			DURIAN_LOG_ERROR("OpenAL: {}", error);
		}
	}
}
