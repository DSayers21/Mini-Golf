#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"
#include "Plane.h"

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
		Vector3f ClosestPoint;
		//X
		if (m_Center.GetX() > other.GetMaxExtents().GetX())
			ClosestPoint.SetX(other.GetMaxExtents().GetX());
		else if (m_Center.GetX() < other.GetMinExtents().GetX())
			ClosestPoint.SetX(other.GetMinExtents().GetX());
		else
			ClosestPoint.SetX(m_Center.GetX());
		//Y
		if (m_Center.GetY() > other.GetMaxExtents().GetY())
			ClosestPoint.SetY(other.GetMaxExtents().GetY());
		else if (m_Center.GetY() < other.GetMinExtents().GetY())
			ClosestPoint.SetY(other.GetMinExtents().GetY());
		else
			ClosestPoint.SetY(m_Center.GetY());
		//Z
		if (m_Center.GetZ() > other.GetMaxExtents().GetZ())
			ClosestPoint.SetZ(other.GetMaxExtents().GetZ());
		else if (m_Center.GetZ() < other.GetMinExtents().GetZ())
			ClosestPoint.SetZ(other.GetMinExtents().GetZ());
		else
			ClosestPoint.SetZ(m_Center.GetZ());

		Vector3f DifferenceVec = m_Center - ClosestPoint;
														
		float DistanceSquared = pow(DifferenceVec.Length(), 2);
		float RadiusSquared = pow(m_Radius, 2);
														//Get max component
		float MaxDistance = ClosestPoint.Max();
		if (DistanceSquared < RadiusSquared)
			std::cerr << "COLLISION" << std::endl;

		return IntersectData(DistanceSquared < RadiusSquared, DifferenceVec);
	}

	void BoundingSphere::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
	}
}