#pragma once

#include <Durian/Event/Event.h>

namespace Durian
{
	struct MouseMovedEvent : public Event
	{
		MouseMovedEvent(int xPos, int yPos)
			: x(xPos), y(yPos)
		{
			m_Name = "Mouse Moved Event";
		}

		int x, y;
	};

	struct MouseButtonDownEvent : public Event
	{
		MouseButtonDownEvent(int button)
			: Button(button)
		{
			m_Name = "Mouse Button Down Event";
		}

		int Button;
	};

	struct MouseButtonUpEvent : public Event
	{
		MouseButtonUpEvent(int button)
			: Button(button)
		{
			m_Name = "Mouse Button Up Event";
		}

		int Button;
	};

	struct MouseScrolledEvent : public Event
	{
		MouseScrolledEvent(float x, float y)
			: xOffset(x), yOffset(y)
		{
			m_Name = "Mouse Scrolled Event";
		}

		float xOffset, yOffset;
	};
}