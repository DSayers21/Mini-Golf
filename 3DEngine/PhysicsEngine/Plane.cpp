#include "Plane.h"

namespace D3DEngine
{
	Plane::Plane(const Vector3f& Normal, float Distance) 
		: m_Normal(Normal), m_Distance(Distance)
	{
	}


	Plane::~Plane()
	{
	}

	Plane Plane::Normalise() const
	{
		float Magnitude = m_Normal.Length();

		return Plane(m_Normal / Magnitude, m_Distance / Magnitude);
	}

	IntersectData Plane::IntersectSphere(const BoundingSphere & other) const
	{
		//Get absolute value
		float DistanceFromSphereCenter = fabs(m_Normal.Dot(other.GetCenter()) + m_Distance);
		float DistanceFromSphere = DistanceFromSphereCenter - other.GetRadius();
		//If DistanceFromSphere < 0 then is intersecting
		return IntersectData(DistanceFromSphere < 0, m_Normal * DistanceFromSphere);
	}
}