#include <Pulp.h>
#include <stdio.h>
#include <Pulp/Events/KeyEvent.h>



// This layer provides example of how event system and input polling can be used
// Here all "player logic" implemented in PlayerLayer, but it is always better to do in separate class
class PlayerLayer : public Pulp::Layer {
public:
	float x = 0;
	float y = 0;
	float speed = 1.0f;

	PlayerLayer()
		:Layer("Player input layer")
	{}

	void OnUpdate() override {
		if (move()) {
			std::stringstream ss;
			ss << "Player position: (" << x << ", " << y << ")";
			PLP_INFO(ss.str());
		}
	}
	void OnEvent(Pulp::Event& event) override {
		Pulp::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Pulp::KeyPressedEvent>(std::bind(&PlayerLayer::Jump, this, std::placeholders::_1));
	}

private:
	bool Jump(Pulp::KeyPressedEvent e) {
		if (e.GetKeyCode() == PLP_KEY_SPACE && !e.GetRepeatCount()) {
			PLP_INFO("Jumped!");
			return true;
		}
		return false;
	}
	bool move() {
		float moveX = 0;
		float moveY = 0;

		if (Pulp::Input::IsKeyPressed(PLP_KEY_D)) {
			moveX += speed;
		}
		if (Pulp::Input::IsKeyPressed(PLP_KEY_A)) {
			moveX -= speed;
		}

		if (Pulp::Input::IsKeyPressed(PLP_KEY_W)) {
			moveY += speed;
		}
		if (Pulp::Input::IsKeyPressed(PLP_KEY_S)) {
			moveY -= speed;
		}

		x += moveX;
		y += moveY;
		return moveX || moveY;
	}
};

class Sandbox : public Pulp::Application {
public:
	Sandbox() 
		: Application(Pulp::WindowProps("Example app: Press WASD to move, Space to jump")) {
		PushLayer(new PlayerLayer());
	}
	~Sandbox() {}
};


Pulp::Application* Pulp::CreateApplication() {
	return new Sandbox();
}