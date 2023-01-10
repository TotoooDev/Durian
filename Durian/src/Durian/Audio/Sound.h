#pragma once
#include <Durian/Core/Ref.h>
#include <string>

namespace Durian
{
	class Sound
	{
	public:
		Sound(const std::string& path);
		~Sound();

		unsigned int GetID() const { return m_ID; }

		friend bool operator<(const Sound& rhs, const Sound& lhs)
		{
			return rhs.GetID() < lhs.GetID();
		}

	private:
        void LoadMP3(const std::string& path);
        void LoadOGG(const std::string& path);
        void LoadOther(const std::string& path);

		unsigned int m_ID;
		bool m_Registered = false;

		friend class AudioEngine;
	};

	struct SoundProperties
	{
		float Volume = 1.0f;
		bool Loop = false; // TODO: Change this to a number of loops
		std::string Name = "New sound";
		Ref<Sound> SoundVar; // TODO: Find a new name
	};
}
