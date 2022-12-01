#pragma once
#include <Durian/Core/Ref.h>
#include <Durian/Audio/Sound.h>
#include <vector>

namespace Durian
{
	class SoundPool
	{
	public:
		void AddSound(Ref<Sound> sound) { m_Sounds.push_back(sound); }
		void RemoveSound(Ref<Sound> sound);

	private:
		std::vector<Ref<Sound>> m_Sounds;
	};
}