#pragma once

namespace Durian
{
	// Base layer class
	class Layer
	{
	public:
		virtual void OnCreate() {}
		virtual void OnUpdate(double timestep) {}
		virtual void OnImGuiRender() {}
	};
}