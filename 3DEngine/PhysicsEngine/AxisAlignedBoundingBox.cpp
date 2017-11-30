#include "AxisAlignedBoundingBox.h"

namespace D3DEngine
{
	//AxisAlignedBoundingBox::AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents) :
	//	Collider(Collider::TYPE_AABB), m_MinExtents(MinExtents), m_MaxExtents(MaxExtents)
	//{
	//}

	AxisAlignedBoundingBox::AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents, Vector3f Center, Vector3f Dims, Vector2f Normal) :
		Collider(Collider::TYPE_AABB), m_MinExtents(MinExtents), m_MaxExtents(MaxExtents), m_Center(Center), m_Dims(Dims), m_Normal(Normal)
	{
		std::cerr << "AABB" << std::endl;
	}

	AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
	{
	}

	IntersectData AxisAlignedBoundingBox::IntersectAABB(const AxisAlignedBoundingBox other) const
	{
		//Vector3f Distance1 = other.GetMinExtents().Sub(m_MaxExtents);
		//Vector3f Distance2 = m_MinExtents.Sub(other.GetMaxExtents());
		//Vector3f Distance = Distance1.Max(Distance2);	//Get max x y and z components
		////Get max component
		//float MaxDistance = Distance.Max();

		return IntersectData(2< 0, Vector3f(0,0,0));
	}

	IntersectData AxisAlignedBoundingBox::IntersectBoundingSphere(const BoundingSphere other) const
	{

		//Vector3f Distance1 = other.GetCenter().Sub(m_MaxExtents);
		//Vector3f Distance2 = m_MinExtents.Sub(other.GetCenter());

		//Vector3f Distance = Distance1.Max(Distance2);	//Get max x y and z components
		//												//Get max component
		//float MaxDistance = Distance.Max();
		//if(MaxDistance < other.GetRadius())
		//	std::cerr << "COLLISION1" << std::endl;

		return IntersectData(5235 < other.GetRadius(), Vector3f(0,0,0));
	}

	void AxisAlignedBoundingBox::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
		m_MinExtents = m_MinExtents + Translation;
		m_MaxExtents = m_MaxExtents + Translation;
	}

	Vector3f AxisAlignedBoundingBox::CalcCenter() const
	{
		//return Vector3f(
		//	((m_MaxExtents.GetX() + m_MinExtents.GetX()) / 2),
		//	((m_MaxExtents.GetY() + m_MinExtents.GetY()) / 2),
		//	((m_MaxExtents.GetZ() + m_MinExtents.GetZ()) / 2));
		return Vector3f();
	}

	Vector3f& AxisAlignedBoundingBox::ClosestPoint(const Vector3f& point) const
	{
		Vector3f ClosestP = point;
		//X
		if (point.GetX() > m_MaxExtents.GetX())
			ClosestP.SetX(m_MaxExtents.GetX());
		else if (point.GetX() < m_MinExtents.GetX())
			ClosestP.SetX(m_MinExtents.GetX());
		else
			ClosestP.SetX(point.GetX());
		//Y
		if (point.GetY() > m_MaxExtents.GetY())
			ClosestP.SetY(m_MaxExtents.GetY());
		else if (point.GetY() < m_MinExtents.GetY())
			ClosestP.SetY(m_MinExtents.GetY());
		else
			ClosestP.SetY(point.GetY());
		//Z
		if (point.GetZ() > m_MaxExtents.GetZ())
			ClosestP.SetZ(m_MaxExtents.GetZ());
		else if (point.GetZ() < m_MinExtents.GetZ())
			ClosestP.SetZ(m_MinExtents.GetZ());
		else
			ClosestP.SetZ(point.GetZ());

		return ClosestP;
	}

	Vector3f& AxisAlignedBoundingBox::ClosestPtPointAABB(const Vector3f& point) const    // P131
	{
		// For each coordinate axis, if the point coordinate value is outside box,
		// clamp it to the box, else keep it as is
		Vector3f min = m_MinExtents;
		Vector3f max = m_MaxExtents;
		/*float X = min.GetX();
		min.SetX(max.GetX());
		max.SetX(X);*/

		Vector3f q = Vector3f(0,0,0);
		float v = 0;

		v = point.GetX();
		v = fmax(v, min.GetX());
		v = fmin(v, max.GetX());
		q.SetX(v);

		v = point.GetY();
		v = fmax(v, min.GetY());
		v = fmin(v, max.GetY());
		q.SetY(v);

		v = point.GetZ();
		v = fmax(v, min.GetZ());
		v = fmin(v, max.GetZ());
		q.SetZ(v);

		return q;
	}
}