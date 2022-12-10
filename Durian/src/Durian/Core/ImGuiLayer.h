#pragma once
#include <Durian/Core/Layer.h>

namespace Durian
{
	class ImGuiLayer : public Layer
	{
	public:
		~ImGuiLayer();

		virtual void OnCreate() override;
		virtual void OnUpdate(double timestep) override {};
		void OnImGuiRender() override {};

		void Begin();
		void End();

	private:
		void SetImGuiTheme();
	};
}