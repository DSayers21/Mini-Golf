#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"
#include "Plane.h"
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

	IntersectData BoundingSphere::IntersectSphere(const Plane & other) const
	{
		//Get absolute value
		float DistanceFromSphereCenter = fabs(other.GetNormal().Dot(m_Center) + other.GetDistance());
		float DistanceFromSphere = DistanceFromSphereCenter - m_Radius;
		//If DistanceFromSphere < 0 then is intersecting
		if(DistanceFromSphere < 0)
			std::cerr << "COLLISION" << std::endl;
		return IntersectData(DistanceFromSphere < 0, Vector3f(other.GetNormal() * DistanceFromSphere));
	}

	IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere & other)
	{
		float RadiusDistance = m_Radius + other.m_Radius;

		Vector3f Direction = other.m_Center.Sub(m_Center); //Pointing at other sphere
		float CenterDistance = Direction.Length();
		Direction = Direction / CenterDistance;	//Manually Normalising

		float Distance = CenterDistance - RadiusDistance;

		return IntersectData(CenterDistance < RadiusDistance, Vector3f(Direction * Distance));
	}

	//https://stackoverflow.com/questions/9323903/most-efficient-elegant-way-to-clip-a-number
	float clamp(float n, float lower, float upper)
	{
		return std::max(lower, std::min(n, upper));
	}

	IntersectData BoundingSphere::IntersectAABB(const AxisAlignedBoundingBox & other)
	{
		float HalfX = other.GetDims().GetX() / 2;
		float HalfY = other.GetDims().GetY() / 2;
		float HalfZ = other.GetDims().GetZ() / 2;

		Vector3f OtherCenter = other.GetCenter();

		Vector3f SpherePos = m_Center;

		Vector3f CollisionThingA(OtherCenter.GetX() + HalfX, OtherCenter.GetY() + HalfY, OtherCenter.GetZ() + HalfZ);
		Vector3f CollisionThingB(OtherCenter.GetX() - HalfX, OtherCenter.GetY() - HalfY, OtherCenter.GetZ() - HalfZ);
		Vector3f CollisionThingC(OtherCenter.GetX() - HalfX, OtherCenter.GetY(), OtherCenter.GetZ() - HalfZ);

		//std::cerr << SpherePos.ToString() << std::endl;

		if (((OtherCenter.GetZ() + HalfZ > SpherePos.GetZ()) && (SpherePos.GetZ() > OtherCenter.GetZ() - HalfZ))
			&& ((OtherCenter.GetX() + HalfX > SpherePos.GetX()) && (SpherePos.GetX() > OtherCenter.GetX() - HalfX))) 
		{
			//std::cerr << other.ClosestPoint(m_Center).ToString() << std::endl;
			Vector3f Closest = other.ClosestPoint(m_Center);
			Vector3f N = (m_Center - other.GetCenter());
			Vector3f Normal = (N - Closest);

			Normal.SetX(N.GetX());
			Normal.SetZ(N.GetZ());

			Normal = Normal.Normalise();

			Vector3f ColNormal = other.GetCenter() - m_Center;
			float uX = sqrtf(pow(ColNormal.GetX(), 2));
			float uZ = sqrtf(pow(ColNormal.GetZ(), 2));

			if (uX == 0)
				uX = 100;
			if (uZ == 0)
				uZ = 100;

			if (other.GetCenter().GetX() == m_Center.GetX())
			{
				std::cerr << "X SAME" << std::endl;
			}

			if (uX > uZ)
			{
				Normal.SetX(0);
				(Normal.GetZ() < 0) ? Normal.SetZ(-1) : Normal.SetZ(1);
			}
			else
			{
				Normal.SetZ(0);
				(Normal.GetX() < 0) ? Normal.SetX(-1) : Normal.SetX(1);
			}
			Normal.SetY(0);
			return IntersectData(true, Normal);
		}
		return IntersectData(false, m_Center);
	}

	void BoundingSphere::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
	}
}