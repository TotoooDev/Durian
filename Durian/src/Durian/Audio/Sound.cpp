#include <pch.h>
#include <Durian/Audio/Sound.h>
#include <Durian/Core/Application.h>

namespace Durian
{
	Sound::Sound(const std::string& path, int loops, int volume, int channel)
		: m_Path(path), m_Loops(loops), m_Volume(volume), m_Channel(channel)
	{
		m_Chunk = Mix_LoadWAV(path.c_str());
		if (!m_Chunk)
		{
			DURIAN_LOG_ERROR("Failed to load chunk at {}!", path);
		}
	}

	Sound::~Sound()
	{
		Mix_FreeChunk(m_Chunk);
	}

	void Sound::SetVolume(int volume)
	{
		m_Volume = volume;
		Mix_VolumeChunk(m_Chunk, m_Volume);
	}
}