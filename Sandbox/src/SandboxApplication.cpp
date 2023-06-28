#include <Pulp.h>
#include <stdio.h>




class MyLayer : public Pulp::Layer {
public:
	MyLayer()
		:Layer("My Layer")
	{}

	void OnUpdate() override {
		if (Pulp::Input::IsKeyPressed(PLP_KEY_G))
			PLP_INFO("g pressed");
		
	}
	void OnEvent(Pulp::Event& event) override {
	}
};

class Sandbox : public Pulp::Application {
public:
	Sandbox() {
		PushLayer(new MyLayer());
	}
	~Sandbox() {}
};


Pulp::Application* Pulp::CreateApplication() {
	return new Sandbox();
}