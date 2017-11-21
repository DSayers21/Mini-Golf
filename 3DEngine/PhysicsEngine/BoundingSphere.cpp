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
		float XDiff = sqrtf(pow(other.GetMaxExtents().GetX() - other.GetMinExtents().GetX(), 2));
		float YDiff = sqrtf(pow(other.GetMaxExtents().GetY() - other.GetMinExtents().GetY(), 2));
		float ZDiff = sqrtf(pow(other.GetMaxExtents().GetZ() - other.GetMinExtents().GetZ(), 2));

		float HalfX = other.GetDims().GetX() / 2;
		float HalfY = other.GetDims().GetY() / 2;
		float HalfZ = other.GetDims().GetZ() / 2;

		Vector3f OtherCenter = other.GetCenter();

		//Vector3f OtherCenter = other.GetCenterPos();

		Vector3f SpherePos = m_Center;

		Vector3f CollisionThingA(OtherCenter.GetX() + HalfX, OtherCenter.GetY() + HalfY, OtherCenter.GetZ() + HalfZ);
		Vector3f CollisionThingB(OtherCenter.GetX() - HalfX, OtherCenter.GetY() - HalfY, OtherCenter.GetZ() - HalfZ);

		/*std::cerr << OtherCenter.GetZ() + HalfZ << " > " << SpherePos.GetZ() << " > " << OtherCenter.GetZ() - HalfZ << std::endl;
		std::cerr << OtherCenter.GetX() + HalfX << " > " << SpherePos.GetX() << " > " << OtherCenter.GetX() - HalfX << std::endl;*/
		if (((OtherCenter.GetZ() + HalfZ > SpherePos.GetZ()) && (SpherePos.GetZ() + m_Radius > OtherCenter.GetZ() - HalfZ))
			&& ((OtherCenter.GetX() + HalfX > SpherePos.GetX()) && (SpherePos.GetX() > OtherCenter.GetX() - HalfX)))
		{
			std::cerr << "Collision" << std::endl;
			return IntersectData(true, m_Center);
		}
		return IntersectData(false, m_Center);
	}

	void BoundingSphere::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
	}
}