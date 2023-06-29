#pragma once
#include "Pulp/Core.h"
#include "plppch.h"


namespace Pulp {
	enum class EventType {
		None = 0,

		WindowClose, WindowResize, 
		WindowMoved,WindowFocus, WindowLostFocus, //currently unimplemented

		AppTick, AppUpdate, AppRender, //currently unimplemented

		KeyPressed, KeyReleased,

		MouseMoved, MouseScrolled,
		MouseButtonPressed, MouseButtonReleased
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,

	};

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){ return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}


	class PULP_API Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> fun) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.Handled = fun(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}
