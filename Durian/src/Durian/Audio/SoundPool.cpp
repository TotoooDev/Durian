#include <pch.h>
#include <Durian/Audio/SoundPool.h>
#include <algorithm>

namespace Durian
{
	void SoundPool::RemoveSound(Ref<Sound> sound)
	{
		auto it = std::find(m_Sounds.begin(), m_Sounds.end(), sound);
		m_Sounds.erase(it);
	}
}