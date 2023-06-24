#include <Pulp.h>
#include <stdio.h>
class Sandbox : public Pulp::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};


Pulp::Application* Pulp::CreateApplication() {
	return new Sandbox();
}