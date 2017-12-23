//Includes
#include "AxisAlignedBoundingBox.h"

namespace D3DEngine
{
	AxisAlignedBoundingBox::AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents, Vector3f Center, Vector3f Dims) :
		Collider(Collider::TYPE_AABB), m_MinExtents(MinExtents), m_MaxExtents(MaxExtents), m_Center(Center), m_Dims(Dims)
	{
		//Display Message
		std::cerr << "Axis Aligned Bounding Box: Created" << std::endl;
	}

	AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
	{
		//Empty
	}

	void AxisAlignedBoundingBox::Transform(const Vector3f Translation)
	{
		//Transform the AABBs position
		m_Center = m_Center + Translation;
		m_MinExtents = m_MinExtents + Translation;
		m_MaxExtents = m_MaxExtents + Translation;
	}

	Vector3f* AxisAlignedBoundingBox::ClosestPtPointAABB(const Vector3f& point) const    // P131
	{
		//Setup Closest Vector
		Vector3f* Closest = new Vector3f(0,0,0);
		float v = 0;
		//Get the closest X posiiton
		v = point.GetX();
		v = fmax(v, m_MinExtents.GetX());
		v = fmin(v, m_MaxExtents.GetX());
		Closest->SetX(v);
		//Get the closest Y posiiton
		v = point.GetY();
		v = fmax(v, m_MinExtents.GetY());
		v = fmin(v, m_MaxExtents.GetY());
		Closest->SetY(v);
		//Get the closest Z posiiton
		v = point.GetZ();
		v = fmax(v, m_MinExtents.GetZ());
		v = fmin(v, m_MaxExtents.GetZ());
		Closest->SetZ(v);
		//Return the closest point
		return Closest;
	}
}