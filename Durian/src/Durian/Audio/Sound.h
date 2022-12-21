#pragma once
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
		unsigned int m_ID;
		bool m_Registered = false;

		friend class AudioEngine;
	};
}