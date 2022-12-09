#include <pch.h>
#include <Durian/Audio/SoundPool.h>
#include <algorithm>

namespace Durian
{
	unsigned int SoundPool::AddSound(Ref<Sound> sound)
	{
		m_Sounds.push_back(sound);
		return m_Sounds.size() - 1;
	}

	void SoundPool::RemoveSound(Ref<Sound> sound)
	{
		auto it = std::find(m_Sounds.begin(), m_Sounds.end(), sound);
		m_Sounds.erase(it);
	}
}