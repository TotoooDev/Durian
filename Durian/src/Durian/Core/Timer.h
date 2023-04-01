#pragma once

#include <chrono>

namespace Durian {
	class Timer
	{
	public:
		Timer()
		{
			Reset();
		}

		void Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		float ElapsedMilliseconds()
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_Start).count();
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};
}