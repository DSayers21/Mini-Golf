#include "AxisAlignedBoundingBox.h"

namespace D3DEngine
{
	AxisAlignedBoundingBox::AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents) :
		Collider(Collider::TYPE_AABB), m_MinExtents(MinExtents), m_MaxExtents(MaxExtents)
	{
	}


	AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
	{
	}

	IntersectData AxisAlignedBoundingBox::IntersectAABB(const AxisAlignedBoundingBox other) const
	{
		Vector3f Distance1 = other.GetMinExtents().Sub(m_MaxExtents);
		Vector3f Distance2 = m_MinExtents.Sub(other.GetMaxExtents());
		Vector3f Distance = Distance1.Max(Distance2);	//Get max x y and z components
		//Get max component
		float MaxDistance = Distance.Max();

		return IntersectData(MaxDistance < 0, Distance);
	}

	IntersectData AxisAlignedBoundingBox::IntersectBoundingSphere(const BoundingSphere other) const
	{

		Vector3f Distance1 = other.GetCenter().Sub(m_MaxExtents);
		Vector3f Distance2 = m_MinExtents.Sub(other.GetCenter());

		Vector3f Distance = Distance1.Max(Distance2);	//Get max x y and z components
														//Get max component
		float MaxDistance = Distance.Max();
		if(MaxDistance < other.GetRadius())
			std::cerr << "COLLISION1" << std::endl;

		return IntersectData(MaxDistance < other.GetRadius(), Distance);
	}

	void AxisAlignedBoundingBox::Transform(const Vector3f Translation)
	{
		//m_MaxExtents = m_MaxExtents + Translation;
		//m_MinExtents = m_MinExtents + Translation;
	}
}