#pragma once

#include "Core.h"

namespace Pulp {
	class PULP_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

