#include "AxisAlignedBoundingBox.h"

namespace D3DEngine
{
	AxisAlignedBoundingBox::AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents) :
		m_MinExtents(MinExtents), m_MaxExtents(MaxExtents)
	{
	}


	AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
	{
	}

	IntersectData AxisAlignedBoundingBox::Intersect(const AxisAlignedBoundingBox other) const
	{
		Vector3f Distance1 = other.GetMinExtents().Sub(m_MaxExtents);
		Vector3f Distance2 = m_MinExtents.Sub(other.GetMaxExtents());
		Vector3f Distance = Distance1.Max(Distance2);	//Get max x y and z components
		//Get max component
		float MaxDistance = Distance.Max();

		return IntersectData(MaxDistance < 0, Distance);
	}
}