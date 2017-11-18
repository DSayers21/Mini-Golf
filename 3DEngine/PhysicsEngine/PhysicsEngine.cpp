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
				IntersectData intersectData = m_Objects[i].GetCollider().Intersect(m_Objects[j].GetCollider());
				//Handle Collision response
				if (intersectData.GetDoesIntersect())
				{
					Vector3f Direction = intersectData.GetDirection().Normalise();
					Vector3f OtherDirection = Direction.Reflect(m_Objects[i].GetVelocity());
					m_Objects[i].SetVelocity(m_Objects[i].GetVelocity().Reflect(OtherDirection));
					m_Objects[j].SetVelocity(m_Objects[j].GetVelocity().Reflect(Direction));

				}
			}
		}
	}
}