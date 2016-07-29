#pragma once

#include "Core/Types.h"
#include "Entity/Guid.h"

#include <memory>
#include <vector>

namespace edn
{
	class Entity;

	class ComponentBase
	{
	public:
		ComponentBase() { }
		virtual ~ComponentBase() { }
	};

	template<typename Type>
	class Component : public ComponentBase
	{
	public:
		Component(const Entity & e);
		~Component() = default;

		static Guid getType();

		virtual String toString() = 0;

		// The owner will never be null to it can be a reference
		const Entity & owner;
	private:
		static Guid type_id;
	};
	
	template<typename Type>
	Guid Component<Type>::type_id = get_guid<Type>();

	template<typename Type>
	Guid Component<Type>::getType()
	{
		return type_id;
	}

	template<typename Type>
	Component<Type>::Component(const Entity & e)
		: owner(e)
	{
	}

	template<typename Type>
	inline String Component<Type>::toString()
	{
		return "Component";
	}
}