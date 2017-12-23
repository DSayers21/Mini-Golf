#pragma once

//Includes
#include <vector>
#include "PhysicsObject.h"
#include "Vert.h"

namespace D3DEngine
{
	class PhysicsEngine
	{
	public:
		//Constructor
		PhysicsEngine();
		//Destructor
		~PhysicsEngine();

		//Clear all objects from the physics engine
		void ClearObjects();

		//Add physics object to the physics engine
		void AddObject(PhysicsObject* object);

		//Add an AABB physics object from a mesh
		void AddAABBFromMesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize);

		void Simulate(float Delta); //Do simulation for all objects
		void HandleCollisions();	//Handle collisions for all physics objects

		//Getters
		inline PhysicsObject* GetObject(unsigned int index) { return m_Objects[index]; }
		inline const unsigned int GetNumObjects() const { return m_Objects.size(); }

	private:
		//List of all physics objects loaded
		std::vector<PhysicsObject*> m_Objects;
	};
}