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

	void PhysicsEngine::HandleCollisions()
	{
		//Go through every object and check for collisions
		for (unsigned int i = 0; i < m_Objects.size(); i++)
		{
			for (unsigned int j = i + 1; j < m_Objects.size(); j++)
			{
				IntersectData intersectData = m_Objects[i].GetBoundingSphere().IntersectBoundingSphere(m_Objects[j].GetBoundingSphere());
				//Handle Collision response
				if (intersectData.GetDoesIntersect())
				{
					Vector3f Velocityi = m_Objects[i].GetVelocity() * -1;
					Vector3f Velocityj = m_Objects[j].GetVelocity() * -1;
					m_Objects[i].SetVelocity(Velocityi);
					m_Objects[j].SetVelocity(Velocityj);
				}
			}
		}
	}
}