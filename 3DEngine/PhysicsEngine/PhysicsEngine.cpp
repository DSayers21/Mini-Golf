#include "PhysicsEngine.h"

namespace D3DEngine
{
	PhysicsEngine::PhysicsEngine()
	{
		
	}

	PhysicsEngine::~PhysicsEngine()
	{
	}

	void PhysicsEngine::AddObject(const PhysicsObject& object)
	{
		m_Objects.push_back(object);
	}

	void PhysicsEngine::Simulate(float Delta)
	{
		for (unsigned int i = 0; i < m_Objects.size(); i++)
		{
			m_Objects[i].Integrate(Delta);
		}
	}
}