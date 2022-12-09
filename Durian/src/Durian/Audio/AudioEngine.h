#pragma once
#include <Durian/Audio/SoundPool.h>
#include <string>

namespace Durian
{
	class AudioEngine
	{
	public:
		unsigned int LoadSound(const std::string& path, int loops = 0, int volume = MIX_MAX_VOLUME, int channel = 0);
		
		void Update();
		void PlaySound(Ref<Sound> sound);
		void SetSoundDistance(Ref<Sound> sound, unsigned char distance);

		Ref<Sound> GetSoundByID(unsigned int id) { return m_SoundPool.GetSound(id); }

	private:
		SoundPool m_SoundPool;
	};
}