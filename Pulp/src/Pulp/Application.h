#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Pulp/LayerStack.h"

namespace Pulp {
	class PULP_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}

