#pragma once

#include <vector>
#include "PhysicsObject.h"

namespace D3DEngine
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();

		void AddObject(const PhysicsObject& object);
		void Simulate(float Delta); //Do simulation for all objects

		//Getters TEMP
		inline const PhysicsObject& GetObject(unsigned int index) const { return m_Objects[index]; }
		inline const unsigned int GetNumObjects() const { return m_Objects.size(); }

	private:
		std::vector<PhysicsObject> m_Objects;
	};
}