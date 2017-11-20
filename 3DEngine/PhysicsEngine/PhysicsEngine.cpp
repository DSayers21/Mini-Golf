#include "PhysicsEngine.h"
#include "AxisAlignedBoundingBox.h"
#include "Plane.h"

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

	void PhysicsEngine::AddAABBFromMesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize)
	{
		for (int i = 0; i < IndexSize-2; i+=3)
		{
			std::cout << "i = " << i << " Index: " << Indices[i] << " = " << Vertices[Indices[i]].GetPos().ToString() << std::endl;
			std::cout << "i = " << i+2 << " Index: " << Indices[i+2] << " = " << Vertices[Indices[i + 2]].GetPos().ToString() << std::endl;

			Vector3f MaxExtents = Vertices[Indices[i]].GetPos();
			Vector3f MinExtents = Vertices[Indices[i+2]].GetPos();
			PhysicsObject* New = new PhysicsObject(new AxisAlignedBoundingBox(MaxExtents, MinExtents), Vector3f(0.0f, 0.0f, 0.0f));
			this->AddObject(*New);
		}
		//for (int i = 0; i < VertSize; i++)
		//{
		//	Vector3f Normal = Vertices[i].GetNormal();
		//	PhysicsObject* New = new PhysicsObject(new Plane(Normal, 0.1f), Vector3f(0.0f,0.0f,0.0f));
		//	this->AddObject(*New);
		//}

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