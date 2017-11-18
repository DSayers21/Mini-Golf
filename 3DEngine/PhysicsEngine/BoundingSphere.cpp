#include "BoundingSphere.h"

namespace D3DEngine
{
	BoundingSphere::BoundingSphere(Vector3f Center, float Radius) :
		Collider(Collider::TYPE_SPHERE), m_Center(Center), m_Radius(Radius)
	{
	}


	BoundingSphere::~BoundingSphere()
	{
	}

	IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere & other)
	{
		float RadiusDistance = m_Radius + other.m_Radius;
		float CenterDistance = Vector3f(m_Center.Sub(other.m_Center)).Length();
		float Distance = CenterDistance - RadiusDistance;

		return IntersectData(CenterDistance < RadiusDistance, Distance);	
	}
}