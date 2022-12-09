#pragma once
#include <string>
#include <SDL2/SDL_mixer.h>

namespace Durian
{
	class Sound
	{
	public:
		Sound(const std::string& path, int loops = 0, int volume = MIX_MAX_VOLUME, int channel = 0);
		~Sound();

		void SetVolume(int volume);

		Mix_Chunk* GetChunk() { return m_Chunk; }
		int GetChannel() { return m_Channel; }
		int GetLoops() { return m_Loops; }
		int GetVolume() { return m_Volume; }
		std::string GetPath() { return m_Path; }

	private:
		Mix_Chunk* m_Chunk;
		std::string m_Path;
		int m_Channel;
		int m_Loops;
		int m_Volume;
	};
}