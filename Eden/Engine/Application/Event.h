#pragma once
#include "Core/Singleton.h"
#include "Core/Platform.h"
#include <functional>
#include <memory>
#include <queue>
#include <vector>

#if defined(EDN_DEBUG)
	#include "Core/Debug.h"
#endif

namespace edn
{
	class EventBase
	{
	public:
		virtual ~EventBase() = default;
		virtual bool has_listeners() const = 0;
		virtual void raise() const = 0;
	};

	template <class EventType>
	class Listener
	{
		static_assert(std::is_base_of<EventBase, EventType>::value, "Template argument must inherit from Event.");
	public:
		Listener() { EventType::subscribe(*this); }
		Listener(std::function<void(const EventType&)> callbackFunc) : callback(callbackFunc) { EventType::subscribe(*this); }
		~Listener() { EventType::unsubscribe(*this); }

		std::function<void(const EventType&)> callback;
	};

	template <class derived>
	class Event : public EventBase
	{
	public:
		virtual ~Event() = default;

		virtual bool has_listeners() const final override
		{
			return has_listeners_static();
		}

		virtual void raise() const final override
		{
			for (unsigned i = 0; i < _listeners.size(); i++)
				if (_listeners[i]->callback)
					_listeners[i]->callback(*static_cast<const derived*>(this));
		}

		static bool has_listeners_static()
		{
			return !_listeners.empty();
		}

		static void subscribe(Listener<derived>& listener)
		{
			_listeners.push_back(&listener);
		}

		static void unsubscribe(Listener<derived>& listener)
		{
			_listeners.erase(std::find(_listeners.begin(), _listeners.end(), &listener));
		}

	private:
		static std::vector<Listener<derived>*> _listeners;
	};
	template<class derived> std::vector<Listener<derived>*> Event<derived>::_listeners;

	static class EventQueue : public Singleton<class EventQueue>
	{
	public:
		void push(std::unique_ptr<EventBase> e)
		{
			#if defined(EDN_DEBUG)
				ASSERT(!is_dispatching, "Cannot push an event while event queue is being processed. Try calling Dispatch(const EventBase&) to bypass the event queue.");
			#endif
			if (e->has_listeners())
				eventQueue.push(std::move(e));
		}

		void dispatch(const EventBase& e) const
		{
			e.raise();
		}

		void dispatch()
		{
			#if defined(EDN_DEBUG)
				is_dispatching = true;
			#endif

			while (!eventQueue.empty())
			{
				eventQueue.front()->raise();
				eventQueue.pop();
			}

			#if defined(EDN_DEBUG)
				is_dispatching = false;
			#endif
		}

	private:
		std::queue<std::unique_ptr<EventBase>> eventQueue;

#ifdef _DEBUG
		bool is_dispatching = false;
#endif
	} &EventQueue = Singleton<class EventQueue>::instanceRef;
}