//Includes
#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"
#include <iostream>
#include <algorithm>

namespace D3DEngine
{
	BoundingSphere::BoundingSphere(Vector3f Center, float Radius) :
		Collider(Collider::TYPE_SPHERE), m_Center(Center), m_Radius(Radius)
	{
		//Empty
	}

	BoundingSphere::~BoundingSphere()
	{
		//Empty
	}

	IntersectData* BoundingSphere::IntersectBoundingSphere(const BoundingSphere & other)
	{
		//Get the radius distance
		float RadiusDistance = m_Radius + other.m_Radius;
		//Get the direction between the two spheres
		Vector3f Direction = other.m_Center.Sub(m_Center); //Pointing at other sphere
		float CenterDistance = Direction.Length();
		Direction = Direction / CenterDistance;	//Manually Normalising
		//Calculate the distance
		float Distance = CenterDistance - RadiusDistance;
		//Return the intersection data
		return new IntersectData(CenterDistance < RadiusDistance, Vector3f(Direction * Distance));
	}

	//Collision correct normal
	//https://www.gamedev.net/forums/topic/550776-solved-c-spherebox-collision---correct-normal-but-resolution-is-not-correct/
	IntersectData* BoundingSphere::IntersectAABB(const AxisAlignedBoundingBox & other)
	{
		//Find point (ClosestP) on AABB closest to Sphere center
		Vector3f* ClosestP = other.ClosestPtPointAABB(m_Center);

		//Sphere and AABB intersect if the (squared) distance from sphere center to point (ClosestP)
		//is less than the (squared) sphere radius
		Vector3f v = ClosestP->Sub(m_Center);
		
		if (v.Dot(v) <= powf(m_Radius, 2))
		{
			//Calculate the distance
			float Distance = other.GetCenter().Distance(m_Center);

			//Calculate normal using sphere center a closest point on AABB
			Vector3f ContactNormal = m_Center - *ClosestP;
			//If the normal is not 0
			if (ContactNormal != Vector3f(0,0,0))
			{
				//Display message
				std::cerr << "Collision" << std::endl;
				//Set the normal
				ContactNormal = ContactNormal.Normalise();
			}
			else
			{
				//Display message
				std::cerr << "Inside Collision" << std::endl;
				//Sphere is inside AABB, set the Normal to out of the AABB
				ContactNormal = Vector3f(1,0,0);
			}
			//Delete the closest point vector
			delete ClosestP;
			//Return the intersection data
			return new IntersectData(true, ContactNormal);
		}
		//Delete the closest point vector
		delete ClosestP;
		// No intersection, return intersection data
		return new IntersectData(false, m_Center);
	}

	void BoundingSphere::Transform(const Vector3f Translation)
	{
		//Transform the center by the translation vector
		m_Center = m_Center + Translation;
	}
}