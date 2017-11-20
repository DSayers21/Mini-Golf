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
		//float x = std::max(other.GetMinExtents().GetX(), std::min(m_Center.GetX(), other.GetMaxExtents().GetX()));
		//float y = std::max(other.GetMinExtents().GetY(), std::min(m_Center.GetY(), other.GetMaxExtents().GetY()));
		//float z = std::max(other.GetMinExtents().GetZ(), std::min(m_Center.GetZ(), other.GetMaxExtents().GetZ()));

		//Vector3f ClosestPoint(x, y, z);
		////std::cerr << ClosestPoint.ToString() << std::endl;
		//float Dis = ClosestPoint.Distance(m_Center);

		//std::cerr << Dis << std::endl;

		//if (Dis < m_Radius)
		//{
		//	std::cerr << "COLLISION: " << Dis << std::endl;
		//	std::cerr << "MaxExtents: (" << other.GetMaxExtents().GetX() << " , " << other.GetMaxExtents().GetY() << " , " << other.GetMaxExtents().GetZ() << ")";
		//	std::cerr << ": MinExtents: (" << other.GetMinExtents().GetX() << " , " << other.GetMinExtents().GetY() << " , " << other.GetMinExtents().GetZ() << ")" << std::endl;
		//	std::cerr << "Center: " << m_Center.ToString() << std::endl;
		//}
		/*float  dmin;
		float  r2 = pow(m_Radius, 2);
		dmin = 0;

		if (m_Center.GetX() < other.GetMinExtents().GetX())
			dmin += pow(m_Center.GetX() - other.GetMinExtents().GetX(), 2);
		else if (m_Center.GetX() > other.GetMaxExtents().GetX())
			dmin += pow(m_Center.GetX() - other.GetMaxExtents().GetX(), 2);
		
		if (m_Center.GetY() < other.GetMinExtents().GetY())
			dmin += pow(m_Center.GetY() - other.GetMinExtents().GetY(), 2);
		else if (m_Center.GetY() > other.GetMaxExtents().GetY())
			dmin += pow(m_Center.GetY() - other.GetMaxExtents().GetY(), 2);

		if (m_Center.GetZ() < other.GetMinExtents().GetZ())
			dmin += pow(m_Center.GetZ() - other.GetMinExtents().GetZ(), 2);
		else if (m_Center.GetZ() > other.GetMaxExtents().GetZ())
			dmin += pow(m_Center.GetZ() - other.GetMaxExtents().GetZ(), 2);

		if (dmin < r2)
		{
			return IntersectData(true, m_Center);
		}*/

		float  a, b;
		float  dmin, dmax;
		float  r2 = (float)pow(m_Radius, 2);
		int    i, face;
		float  Bmin[3];  /* The minimum of the box for each axis.  */
		float  Bmax[3];  /* The maximum of the box for each axis. */
		float  C[3];

		Bmin[0] = other.GetMinExtents().GetX();
		Bmin[1] = other.GetMinExtents().GetY();
		Bmin[2] = other.GetMinExtents().GetZ();
		Bmax[0] = other.GetMaxExtents().GetX();
		Bmax[1] = other.GetMaxExtents().GetY();
		Bmax[2] = other.GetMaxExtents().GetZ();
		C[0] = m_Center.GetX();
		C[1] = m_Center.GetY();
		C[2] = m_Center.GetZ();

		dmin = 0;
		dmax = 0;
		face = false;

		for (i = 0; i < 3; i++) {
			a = pow(C[i] - Bmin[i], 2);
			b = pow(C[i] - Bmax[i], 2);
			dmax += std::max(a, b);
			if (C[i] < Bmin[i]) {
				face = true;
				dmin += a;
			}
			else if (C[i] > Bmax[i]) {
				face = true;
				dmin += b;
			}
			else if (std::min(a, b) <= r2) face = true;
		}
		if (face && (dmin <= r2) && (r2 <= dmax)) 
			return(IntersectData(true, m_Center));

		return IntersectData(false, m_Center);
	}

	void BoundingSphere::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
	}
}