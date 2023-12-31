#pragma once

#ifdef PLP_PLATFORM_WINDOWS

extern Pulp::Application* Pulp::CreateApplication();

int main(int argc, char** argv)
{
	Pulp::Log::Init();

	auto app = Pulp::CreateApplication();
	app->Run();
	delete app;
}

#endif // PLP_PLATFORM_WINDOWSEBUG

