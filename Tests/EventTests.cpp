#pragma once
#include <CppUnitTest.h>
#include <Pulp/Events/Event.h>
#include <Pulp/Events/ApplicationEvent.h>
#include <Pulp/Events/KeyEvent.h>
#include <Pulp/Events/MouseEvent.h>


namespace EventTests {
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	TEST_CLASS(ApplicationEvents) {

		TEST_METHOD(CategoryTest) {
			Pulp::WindowCloseEvent windowClose;
			Assert::IsTrue(windowClose.GetCategoryFlags() & Pulp::EventCategory::EventCategoryApplication);

			Pulp::WindowResizeEvent windowResize(0, 0);
			Assert::IsTrue(windowResize.GetCategoryFlags() & Pulp::EventCategory::EventCategoryApplication);
		}

		TEST_METHOD(TypeTest) {
			Pulp::WindowCloseEvent windowClose;
			Assert::IsTrue(windowClose.GetEventType() == Pulp::WindowCloseEvent::GetStaticType());
			Assert::IsTrue(windowClose.GetEventType() == windowClose.GetStaticType());
			Assert::IsTrue(windowClose.GetEventType() == Pulp::EventType::WindowClose);

			Pulp::WindowResizeEvent windowResize(0, 0);
			Assert::IsTrue(windowResize.GetEventType() == Pulp::WindowResizeEvent::GetStaticType());
			Assert::IsTrue(windowResize.GetEventType() == windowResize.GetStaticType());
			Assert::IsTrue(windowResize.GetEventType() == Pulp::EventType::WindowResize);
		}
	};
	TEST_CLASS(KeyEvents) {
		TEST_METHOD(CategoryTest) {
			Pulp::KeyPressedEvent keyPressed(0, 0);
			Assert::IsTrue(keyPressed.GetCategoryFlags() & Pulp::EventCategory::EventCategoryKeyboard);
			Assert::IsTrue(keyPressed.GetCategoryFlags() & Pulp::EventCategory::EventCategoryInput);

			Pulp::KeyReleasedEvent keyReleased(0);
			Assert::IsTrue(keyReleased.GetCategoryFlags() & Pulp::EventCategory::EventCategoryKeyboard);
			Assert::IsTrue(keyReleased.GetCategoryFlags() & Pulp::EventCategory::EventCategoryInput);
		}

		TEST_METHOD(TypeTest) {
			Pulp::KeyPressedEvent keyPressed(0, 0);
			Assert::IsTrue(keyPressed.GetEventType() == Pulp::KeyPressedEvent::GetStaticType());
			Assert::IsTrue(keyPressed.GetEventType() == keyPressed.GetStaticType());
			Assert::IsTrue(keyPressed.GetEventType() == Pulp::EventType::KeyPressed);

			Pulp::KeyReleasedEvent keyReleased(0);
			Assert::IsTrue(keyReleased.GetEventType() == Pulp::KeyReleasedEvent::GetStaticType());
			Assert::IsTrue(keyReleased.GetEventType() == keyReleased.GetStaticType());
			Assert::IsTrue(keyReleased.GetEventType() == Pulp::EventType::KeyReleased);
		}
	};
	TEST_CLASS(MouseEvents) {
		TEST_METHOD(CategoryTest) {
			Pulp::MouseButtonPressedEvent buttonPressed(0);
			Assert::IsTrue(buttonPressed.GetCategoryFlags() & Pulp::EventCategory::EventCategoryMouse);
			Assert::IsTrue(buttonPressed.GetCategoryFlags() & Pulp::EventCategory::EventCategoryInput);

			Pulp::MouseButtonReleasedEvent buttonReleased(0);
			Assert::IsTrue(buttonReleased.GetCategoryFlags() & Pulp::EventCategory::EventCategoryMouse);
			Assert::IsTrue(buttonReleased.GetCategoryFlags() & Pulp::EventCategory::EventCategoryInput);


			Pulp::MouseMovedEvent mouseMoved(0, 0);
			Assert::IsTrue(mouseMoved.GetCategoryFlags() & Pulp::EventCategory::EventCategoryMouse);
			Assert::IsTrue(mouseMoved.GetCategoryFlags() & Pulp::EventCategory::EventCategoryInput);

			Pulp::MouseScrolledEvent mouseScrolled(0, 0);
			Assert::IsTrue(mouseScrolled.GetCategoryFlags() & Pulp::EventCategory::EventCategoryMouse);
			Assert::IsTrue(mouseScrolled.GetCategoryFlags() & Pulp::EventCategory::EventCategoryInput);
		}

		TEST_METHOD(TypeTest) {
			Pulp::MouseButtonPressedEvent buttonPressed(0);
			Assert::IsTrue(buttonPressed.GetEventType() == Pulp::MouseButtonPressedEvent::GetStaticType());
			Assert::IsTrue(buttonPressed.GetEventType() == buttonPressed.GetStaticType());
			Assert::IsTrue(buttonPressed.GetEventType() == Pulp::EventType::MouseButtonPressed);

			Pulp::MouseButtonReleasedEvent buttonReleased(0);
			Assert::IsTrue(buttonReleased.GetEventType() == Pulp::MouseButtonReleasedEvent::GetStaticType());
			Assert::IsTrue(buttonReleased.GetEventType() == buttonReleased.GetStaticType());
			Assert::IsTrue(buttonReleased.GetEventType() == Pulp::EventType::MouseButtonReleased);


			Pulp::MouseMovedEvent mouseMoved(0, 0);
			Assert::IsTrue(mouseMoved.GetEventType() == Pulp::MouseMovedEvent::GetStaticType());
			Assert::IsTrue(mouseMoved.GetEventType() == mouseMoved.GetStaticType());
			Assert::IsTrue(mouseMoved.GetEventType() == Pulp::EventType::MouseMoved);

			Pulp::MouseScrolledEvent mouseScrolled(0, 0);
			Assert::IsTrue(mouseScrolled.GetEventType() == Pulp::MouseScrolledEvent::GetStaticType());
			Assert::IsTrue(mouseScrolled.GetEventType() == mouseScrolled.GetStaticType());
			Assert::IsTrue(mouseScrolled.GetEventType() == Pulp::EventType::MouseScrolled);
		}
	};
	TEST_CLASS(EventsOther) {
		TEST_METHOD(EventDispatcherTest) {
			class temp {
			public:
				bool ReturnsTrue(Pulp::MouseScrolledEvent e) { return true; }
				bool ReturnsFalse(Pulp::MouseScrolledEvent e) { return false; }
				bool ReturnsTrueAnotherEvent(Pulp::MouseButtonPressedEvent e) { Assert::Fail(); return true; }
				bool ReturnsFalseAnotherEvent(Pulp::MouseButtonPressedEvent e) { Assert::Fail(); return false; }
			};

			Pulp::MouseScrolledEvent* e;
			Pulp::EventDispatcher* dispatcher;
			bool dispatched, handled;


			e = new Pulp::MouseScrolledEvent(1, 2);
			dispatcher = new Pulp::EventDispatcher(*e);

			dispatched = dispatcher->Dispatch<Pulp::MouseScrolledEvent>(std::bind(&temp::ReturnsTrue, new temp(), std::placeholders::_1));
			handled = e->Handled;
			Assert::IsTrue(dispatched);
			Assert::IsTrue(handled);

			delete e;
			delete dispatcher;


			e = new Pulp::MouseScrolledEvent(1, 2);
			dispatcher = new Pulp::EventDispatcher(*e);

			dispatched = dispatcher->Dispatch<Pulp::MouseScrolledEvent>(std::bind(&temp::ReturnsFalse, new temp(), std::placeholders::_1));
			handled = e->Handled;
			Assert::IsTrue(dispatched);
			Assert::IsFalse(handled);

			delete e;
			delete dispatcher;


			e = new Pulp::MouseScrolledEvent(1, 2);
			dispatcher = new Pulp::EventDispatcher(*e);

			dispatched = dispatcher->Dispatch<Pulp::MouseButtonPressedEvent>(
				std::bind(&temp::ReturnsTrueAnotherEvent, new temp(), std::placeholders::_1));
			handled = e->Handled;
			Assert::IsFalse(dispatched);
			Assert::IsFalse(handled);

			delete e;
			delete dispatcher;


			e = new Pulp::MouseScrolledEvent(1, 2);
			dispatcher = new Pulp::EventDispatcher(*e);

			dispatched = dispatcher->Dispatch<Pulp::MouseButtonPressedEvent>(
				std::bind(&temp::ReturnsFalseAnotherEvent, new temp(), std::placeholders::_1));
			handled = e->Handled;
			Assert::IsFalse(dispatched);
			Assert::IsFalse(handled);

			delete e;
			delete dispatcher;
		}
	};
}