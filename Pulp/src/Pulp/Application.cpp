#include "plppch.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Log.h"

namespace Pulp {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent wr(100, 200);
		PLP_TRACE(wr);
		WindowCloseEvent wc;
		PLP_TRACE(wc);

		KeyPressedEvent kp(1, 2);
		PLP_TRACE(kp);
		KeyReleasedEvent kr(1);
		PLP_TRACE(kr);

		MouseMovedEvent mm(12, 34);
		PLP_TRACE(mm);
		MouseScrolledEvent ms(56, 78);
		PLP_TRACE(ms);

		MouseButtonPressedEvent mp(777);
		PLP_TRACE(mp);
		MouseButtonReleasedEvent mr(777);
		PLP_TRACE(mr);

	}
}
