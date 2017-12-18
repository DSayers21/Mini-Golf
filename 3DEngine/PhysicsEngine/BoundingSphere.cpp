#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"
#include <iostream>
#include <algorithm>

namespace D3DEngine
{
	BoundingSphere::BoundingSphere(Vector3f Center, float Radius) :
		Collider(Collider::TYPE_SPHERE), m_Center(Center), m_Radius(Radius)
	{
	}


	BoundingSphere::~BoundingSphere()
	{

	}

	IntersectData* BoundingSphere::IntersectBoundingSphere(const BoundingSphere & other)
	{
		float RadiusDistance = m_Radius + other.m_Radius;

		Vector3f Direction = other.m_Center.Sub(m_Center); //Pointing at other sphere
		float CenterDistance = Direction.Length();
		Direction = Direction / CenterDistance;	//Manually Normalising

		float Distance = CenterDistance - RadiusDistance;

		return new IntersectData(CenterDistance < RadiusDistance, Vector3f(Direction * Distance));
	}

	//https://www.gamedev.net/forums/topic/550776-solved-c-spherebox-collision---correct-normal-but-resolution-is-not-correct/
	IntersectData* BoundingSphere::IntersectAABB(const AxisAlignedBoundingBox & other)
	{
		// Find point (p) on AABB closest to Sphere center
		Vector3f* p = other.ClosestPtPointAABB(m_Center);

		// Sphere and AABB intersect if the (squared) distance from sphere center to point (p)
		// is less than the (squared) sphere radius
		Vector3f v = p->Sub(m_Center);
		
		if (v.Dot(v) <= powf(m_Radius, 2))
		{
			float Distance = other.GetCenter().Distance(m_Center);

			// Calculate normal using sphere center a closest point on AABB
			Vector3f contact_Normal = m_Center - *p;

			if (contact_Normal != Vector3f(0,0,0))
			{
				std::cerr << "Collision" << std::endl;
				contact_Normal = contact_Normal.Normalise();
			}
			else
			{
				std::cerr << "Inside Collision" << std::endl;
				// Sphere is inside AABB
				contact_Normal = Vector3f(1,0,0);
			}
			delete p;
			return new IntersectData(true, contact_Normal);
		}
		delete p;
		// No intersection
		return new IntersectData(false, m_Center);
	}

	void BoundingSphere::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
	}
}