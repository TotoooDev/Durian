#pragma once
#include <Durian/Audio/Sound.h>
#include <Durian/Core/Ref.h>
#include <map>
#include <AL/alc.h>

namespace Durian
{
	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void PlaySound(Ref<Sound> sound);
		void StopSound(Ref<Sound> sound);
		bool IsPlaying();

		void PrintErrors();

	private:
		ALCdevice* m_Device = nullptr;
		ALCcontext* m_Context = nullptr;
		std::map<Ref<Sound>, unsigned int> m_Sources;
	};
}