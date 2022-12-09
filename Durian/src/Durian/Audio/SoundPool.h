#pragma once
#include <Durian/Core/Ref.h>
#include <Durian/Audio/Sound.h>
#include <vector>

namespace Durian
{
	class SoundPool
	{
	public:
		unsigned int AddSound(Ref<Sound> sound);
		void RemoveSound(Ref<Sound> sound);
		Ref<Sound> GetSound(unsigned int id) { return m_Sounds.at(id); }

		unsigned int GetSize() { return m_Sounds.size(); }
		std::vector<Ref<Sound>>::iterator begin() { return m_Sounds.begin(); }
		std::vector<Ref<Sound>>::iterator end() { return m_Sounds.end(); }

	private:
		std::vector<Ref<Sound>> m_Sounds;
	};
}