//Includes
#include "PhysicsEngine.h"
#include "AxisAlignedBoundingBox.h"

namespace D3DEngine
{
	PhysicsEngine::PhysicsEngine()
	{
		//Empty
	}

	PhysicsEngine::~PhysicsEngine()
	{
		//Empty
	}

	void PhysicsEngine::ClearObjects()
	{
		//Clear all physics objects
		m_Objects.clear();
	}

	void PhysicsEngine::AddObject(PhysicsObject* object)
	{
		//Add physics object to the list
		m_Objects.push_back(object);
	}

	void PhysicsEngine::AddAABBFromMesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize)
	{
		//Find two points furthest apart
		Vector3f PointMin;
		Vector3f PointMax;
		//Current largest
		float Largest = 0;

		//Loop through all verts, to find the two verts which are furthest apart
		for (int i = 0; i < VertSize; i++)
		{
			for (int j = i+1; j < VertSize; j++)
			{
				//Get current vert pos
				Vector3f PositionA = Vertices[i].GetPos();
				Vector3f PositionB = Vertices[j].GetPos();
				//Check the verts are not the same
				if (!(PositionA == PositionB))
				{
					//Get the distance between the two points
					float Res = PositionA.Distance(PositionB);
					Res = sqrtf(pow(Res, 2));
					//Check if the distance is greater than the current largest
					if (Res > Largest)
					{
						//Update largest
						Largest = Res;
						//Set min and max points to current
						PointMin = Vertices[i].GetPos();
						PointMax = Vertices[j].GetPos();
					}
				}
			}
		}

		//Check if the min X component is larger than the max X component
		if (PointMin.GetX() > PointMax.GetX())
		{
			//Swap the X components
			float X = PointMin.GetX();
			PointMin.SetX(PointMax.GetX());
			PointMax.SetX(X);
		}

		//Check if the min Z component is larger than the max Z component
		if (PointMin.GetZ() > PointMax.GetZ())
		{
			//Swap the X components
			float Z = PointMin.GetZ();
			PointMin.SetZ(PointMax.GetZ());
			PointMax.SetZ(Z);
		}

		//Get the center position of the AABB
		Vector3f CenterPos(
			((PointMax.GetX() + PointMin.GetX()) / 2),
			((PointMax.GetY() + PointMin.GetY()) / 2),
			((PointMax.GetZ() + PointMin.GetZ()) / 2));

		//Calculate the dimensions of the AABB
		float XDiff = sqrtf(pow(PointMax.GetX() - PointMin.GetX(), 2));
		float YDiff = sqrtf(pow(PointMax.GetY() - PointMin.GetY(), 2));
		float ZDiff = sqrtf(pow(PointMax.GetZ() - PointMin.GetZ(), 2));
		Vector3f Dims(XDiff, YDiff, ZDiff);

		//Create new physics object which is an AABB with the min and max verts
		PhysicsObject* New = new PhysicsObject(new AxisAlignedBoundingBox(PointMin, PointMax, CenterPos, Dims), Vector3f(0.0f, 0.0f, 0.0f));
		//Set the position of the physics object to the CenterPos
		New->SetPosition(CenterPos);
		//Add the new physics object to the physics engine
		this->AddObject(New);
	}

	void PhysicsEngine::Simulate(float Delta)
	{
		//Loop over all physics objects and simulate them
		for (unsigned int i = 0; i < m_Objects.size(); i++)
			m_Objects[i]->Integrate(Delta);
	}

	void PhysicsEngine::HandleCollisions()
	{
		//Get the amount of physics objects
		unsigned int Size = m_Objects.size();
		bool Collided;	//If it has collided

		//Go through every object and check for collisions
		for (unsigned int i = 0; i < Size; i++)
		{
			Collided = false;	//Collided = false
			for (unsigned int j = i + 1; j < Size; j++)
			{
				if (!Collided)	//If no collision yet
				{
					//Get the intersection between the current two physics objects
					IntersectData* IntersectionData = m_Objects[i]->GetCollider()->Intersect(*m_Objects[j]->GetCollider());
					//Handle Collision response
					if (IntersectionData->GetDoesIntersect())
					{
						//Get the velocity
						Vector3f Vel = m_Objects[i]->GetVelocity();
						//Get the direction
						Vector3f Dir = IntersectionData->GetDirection();
						//Calculate the reflected velocity
						Vector3f ReflectVel = Vector3f(Vector3f(Vel - Vector3f( Dir * (Vel.Dot(Dir) / Dir.Dot(Dir)))) - Vector3f(Dir * (Vel.Dot(Dir) / Dir.Dot(Dir))));
	
						//Set velocity of the object to the refleced velocity
						m_Objects[i]->SetVelocity(ReflectVel);

						//Protected against colliding against multiple objects, only can collide with one object in a frame
						Collided = true;
					}
					//Delete the Intersect Data
					delete IntersectionData;
				}
			}
		}
	}
}