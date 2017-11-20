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
		//Find two points furthest apart
		Vector3f PointMin;
		Vector3f PointMax;

		float Largest = 0;
		for (int i = 0; i < VertSize; i++)
			std::cerr << "VERT: " << Vertices[i].GetPos().ToString() << std::endl;

		for (int i = 0; i < VertSize; i++)
		{
			for (int j = i+1; j < VertSize; j++)
			{
				Vector3f PositionA = Vertices[i].GetPos();
				Vector3f PositionB = Vertices[j].GetPos();
				if (!(PositionA == PositionB))
				{
					float Res = PositionA.Distance(PositionB);
					Res = sqrtf(pow(Res, 2));
					
					if (Res > Largest)
					{
						Largest = Res;
						PointMin = Vertices[i].GetPos();
						PointMax = Vertices[j].GetPos();

						std::cerr << "i: " << i << "  PosMin: " << Vertices[i].GetPos().ToString() << std::endl;
						std::cerr << "j: " << j << "  PosMax: " << Vertices[j].GetPos().ToString() << std::endl;
					}
				}
			}
		}
		PhysicsObject* New = new PhysicsObject(new AxisAlignedBoundingBox(PointMax, PointMin), Vector3f(0.0f, 0.0f, 0.0f));
		this->AddObject(*New);
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
					//Vector3f Direction = intersectData.GetDirection().Normalise();
					//Vector3f OtherDirection = Direction.Reflect(m_Objects[i].GetVelocity());
					//m_Objects[i].SetVelocity(m_Objects[i].GetVelocity().Reflect(OtherDirection));
					////m_Objects[j].SetVelocity(m_Objects[j].GetVelocity().Reflect(Direction));

					Vector3f Direction = m_Objects[i].GetVelocity() * -1;
					Vector3f OtherDirection = m_Objects[j].GetVelocity() * -1;
					m_Objects[i].SetVelocity(Direction);
					m_Objects[j].SetVelocity(OtherDirection);

				}
			}
		}
	}
}