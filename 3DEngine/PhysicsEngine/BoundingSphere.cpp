#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"
#include "Plane.h"
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

	IntersectData BoundingSphere::IntersectAABB(const AxisAlignedBoundingBox & other)
	{
		float x = std::max(other.GetMinExtents().GetX(), std::min(m_Center.GetX(), other.GetMaxExtents().GetX()));
		float y = std::max(other.GetMinExtents().GetY(), std::min(m_Center.GetY(), other.GetMaxExtents().GetY()));
		float z = std::max(other.GetMinExtents().GetZ(), std::min(m_Center.GetZ(), other.GetMaxExtents().GetZ()));

		Vector3f ClosestPoint(x, y, z);

		float Dis = ClosestPoint.Distance(m_Center);

		//std::cerr << Dis << std::endl;
					
		Vector3f Direction = m_Center.Sub(ClosestPoint); //Pointing at other sphere
		float CenterDistance = Direction.Length();
		Direction = Direction / CenterDistance;	//Manually Normalising
		float RadiusDistance = m_Radius + Dis;
		float Distance = CenterDistance - RadiusDistance;


		if (Dis < m_Radius)
		{
			std::cerr << "COLLISION: " << Dis << std::endl;
			std::cerr << "MaxExtents: (" << other.GetMaxExtents().GetX() << " , " << other.GetMaxExtents().GetY() << " , " << other.GetMaxExtents().GetZ() << ")";
			std::cerr << ": MinExtents: (" << other.GetMinExtents().GetX() << " , " << other.GetMinExtents().GetY() << " , " << other.GetMinExtents().GetZ() << ")" << std::endl;
			std::cerr << "Center: " << m_Center.ToString() << std::endl;
		}

		return IntersectData(Dis < m_Radius, Vector3f(Direction * Distance));
	}

	void BoundingSphere::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
	}
}