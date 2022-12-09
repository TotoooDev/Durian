#include <pch.h>
#include <Durian/Audio/AudioEngine.h>

namespace Durian
{
	unsigned int AudioEngine::LoadSound(const std::string& path, int loops, int volume, int channel)
	{
		unsigned int i = 0;
		for (auto& sound : m_SoundPool)
		{
			if (sound->GetPath() == path)
				return i;
			i++;
		}

		Ref<Sound> sound = CreateRef<Sound>(path, loops, volume, channel);
		return m_SoundPool.AddSound(sound);
	}

	void AudioEngine::Update()
	{
		for (auto& sound : m_SoundPool)
		{
			Mix_VolumeChunk(sound->GetChunk(), sound->GetVolume());
		}
	}

	void AudioEngine::PlaySound(Ref<Sound> sound)
	{
		Mix_PlayChannel(sound->GetChannel(), sound->GetChunk(), sound->GetLoops());
	}

	void AudioEngine::SetSoundDistance(Ref<Sound> sound, unsigned char distance)
	{
		Mix_SetDistance(sound->GetChannel(), distance);
	}
}