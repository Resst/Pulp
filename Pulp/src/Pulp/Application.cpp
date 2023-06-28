#include "plppch.h"
#include "Application.h"

#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"

#include <glad/glad.h>

namespace Pulp {
#define BIND_EVENT_FUN(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		PLP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUN(OnEvent));
	}

	Application::~Application()
	{
	}
	void Application::Run()
	{
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();

			//if (Input::IsKeyPressed(PLP_KEY_D))
			//	PLP_CORE_INFO("5 pressed");
			//
			//keybd_event('D', 0, 0, 0);
			
		}

	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e){
		m_Running = false;
		return true;
	}
}
