#include "AxisAlignedBoundingBox.h"

namespace D3DEngine
{
	AxisAlignedBoundingBox::AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents, Vector3f Center, Vector3f Dims, Vector2f Normal) :
		Collider(Collider::TYPE_AABB), m_MinExtents(MinExtents), m_MaxExtents(MaxExtents), m_Center(Center), m_Dims(Dims), m_Normal(Normal)
	{
		std::cerr << "Axis Aligned Bounding Box: Created" << std::endl;
	}

	AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
	{
	}

	void AxisAlignedBoundingBox::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
		m_MinExtents = m_MinExtents + Translation;
		m_MaxExtents = m_MaxExtents + Translation;
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

	Vector3f* AxisAlignedBoundingBox::ClosestPtPointAABB(const Vector3f& point) const    // P131
	{
		// For each coordinate axis, if the point coordinate value is outside box,
		// clamp it to the box, else keep it as is
		/*Vector3f* min = &m_MinExtents;
		Vector3f* max = &m_MaxExtents;*/

		Vector3f* q = new Vector3f(0,0,0);
		float v = 0;

		v = point.GetX();
		v = fmax(v, m_MinExtents.GetX());
		v = fmin(v, m_MaxExtents.GetX());
		q->SetX(v);

		v = point.GetY();
		v = fmax(v, m_MinExtents.GetY());
		v = fmin(v, m_MaxExtents.GetY());
		q->SetY(v);

		v = point.GetZ();
		v = fmax(v, m_MinExtents.GetZ());
		v = fmin(v, m_MaxExtents.GetZ());
		q->SetZ(v);

		return q;
	}
}