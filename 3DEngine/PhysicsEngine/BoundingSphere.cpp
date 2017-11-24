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
		//float XDiff = sqrtf(pow(other.GetMaxExtents().GetX() - other.GetMinExtents().GetX(), 2));
		//float YDiff = sqrtf(pow(other.GetMaxExtents().GetY() - other.GetMinExtents().GetY(), 2));
		//float ZDiff = sqrtf(pow(other.GetMaxExtents().GetZ() - other.GetMinExtents().GetZ(), 2));

		float HalfX = other.GetDims().GetX() / 2;
		float HalfY = other.GetDims().GetY() / 2;
		float HalfZ = other.GetDims().GetZ() / 2;

		Vector3f OtherCenter = other.GetCenter();

		Vector3f SpherePos = m_Center;

		Vector3f CollisionThingA(OtherCenter.GetX() + HalfX, OtherCenter.GetY() + HalfY, OtherCenter.GetZ() + HalfZ);
		Vector3f CollisionThingB(OtherCenter.GetX() - HalfX, OtherCenter.GetY() - HalfY, OtherCenter.GetZ() - HalfZ);
		Vector3f CollisionThingC(OtherCenter.GetX() - HalfX, OtherCenter.GetY(), OtherCenter.GetZ() - HalfZ);

		if (((OtherCenter.GetZ() + HalfZ > SpherePos.GetZ()) && (SpherePos.GetZ() + m_Radius > OtherCenter.GetZ() - HalfZ))
			&& ((OtherCenter.GetX() + HalfX > SpherePos.GetX()) && (SpherePos.GetX() + m_Radius > OtherCenter.GetX() - HalfX)))
		{
			std::cerr << "Collision" << std::endl;
			Vector3f Direction(0,0,0);
			//Get Normal, not working
			Vector3f a = CollisionThingB;
			Vector3f b = CollisionThingA;
			Vector3f c = CollisionThingC;

			Vector3f Vertex1 = (a - c);
			Vertex1 = Vertex1.Normalise();
			Vector3f Vertex2 = (b - c);
			Vertex2 = Vertex2.Normalise();
			//Calc Normal
			Vector3f Normal = Vertex1.CrossProduct(Vertex2);

			std::cerr << Normal.ToString() << std::endl;

			return IntersectData(true, Vector3f(0.1,0,0));
		}
		return IntersectData(false, m_Center);
	}

	void BoundingSphere::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
	}
}