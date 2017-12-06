#pragma once

#include <vector>
#include "PhysicsObject.h"
#include "Vert.h"

namespace D3DEngine
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();
		void ClearObjects();

		void AddObject(PhysicsObject* object);
		void AddAABBFromMesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize);

		void Simulate(float Delta); //Do simulation for all objects
		void HandleCollisions();

		//Getters TEMP
		inline PhysicsObject* GetObject(unsigned int index) { return m_Objects[index]; }
		inline const unsigned int GetNumObjects() const { return m_Objects.size(); }

	private:
		std::vector<PhysicsObject*> m_Objects;
	};
}