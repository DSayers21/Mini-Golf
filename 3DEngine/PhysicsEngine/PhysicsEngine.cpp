#include "PhysicsEngine.h"
#include "AxisAlignedBoundingBox.h"

namespace D3DEngine
{
	PhysicsEngine::PhysicsEngine()
	{
		
	}

	PhysicsEngine::~PhysicsEngine()
	{
	}

	void PhysicsEngine::ClearObjects()
	{
		//for (int i = 0; i < m_Objects.size(); i++)
		//{
			//delete m_Objects[i];
		//}
		m_Objects.clear();
	}

	void PhysicsEngine::AddObject(PhysicsObject* object)
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
					}
				}
			}
		}
		float XDiff = sqrtf(pow(PointMax.GetX() - PointMin.GetX(), 2));
		float YDiff = sqrtf(pow(PointMax.GetY() - PointMin.GetY(), 2));
		float ZDiff = sqrtf(pow(PointMax.GetZ() - PointMin.GetZ(), 2));
		Vector3f Dims(XDiff, YDiff, ZDiff);
		Vector3f CenterPos(
			((PointMax.GetX() + PointMin.GetX()) / 2),
			((PointMax.GetY() + PointMin.GetY()) / 2),
			((PointMax.GetZ() + PointMin.GetZ()) / 2));

		Vector2f Temp = Vector3f(PointMax - PointMin).GetXZ();
		Vector2f Normal(Temp.GetY(), -Temp.GetX());
		Normal = Normal.Normalise();

		if (PointMin.GetX() > PointMax.GetX())
		{
			float X = PointMin.GetX();
			PointMin.SetX(PointMax.GetX());
			PointMax.SetX(X);
		}


		PhysicsObject* New = new PhysicsObject(new AxisAlignedBoundingBox(PointMin, PointMax, CenterPos, Dims, Normal), Vector3f(0.0f, 0.0f, 0.0f));
		New->SetPosition(CenterPos);

		this->AddObject(New);
	}

	void PhysicsEngine::Simulate(float Delta)
	{
		for (unsigned int i = 0; i < m_Objects.size(); i++)
		{
			m_Objects[i]->Integrate(Delta);
		}
	}

	void PhysicsEngine::HandleCollisions()
	{
		//Go through every object and check for collisions
		for (unsigned int i = 0; i < m_Objects.size(); i++)
		{
			for (unsigned int j = i + 1; j < m_Objects.size(); j++)
			{
				IntersectData* intersectData = m_Objects[i]->GetCollider()->Intersect(*m_Objects[j]->GetCollider());
				//Handle Collision response
				if (intersectData->GetDoesIntersect())
				{
					//std::cerr << "COLISION" << std::endl;
					Vector3f V = m_Objects[i]->GetVelocity();
					Vector3f N = intersectData->GetDirection();
					Vector3f U = N * (V.Dot(N) / N.Dot(N));
					Vector3f W = V - U;
					Vector3f ReflectedVel = W - U;

					//if moving away from plane, cannot hit
					float Test = V.Dot(N);


					m_Objects[i]->SetVelocity(ReflectedVel);
				}
				delete intersectData;
			}
		}
	}
}