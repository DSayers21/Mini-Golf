#pragma once

#include "Vector3f.h"
#include "IntersectData.h"

namespace D3DEngine
{
	class AxisAlignedBoundingBox
	{
	public:
		AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents);
		~AxisAlignedBoundingBox();

		IntersectData Intersect(const AxisAlignedBoundingBox other) const;

		//Getters
		inline const Vector3f& GetMinExtents() const { return m_MinExtents; }
		inline const Vector3f& GetMaxExtents() const { return m_MaxExtents; }

	private:
		//Two Extreme Corners
		const Vector3f m_MinExtents;	//Bottom left corner
		const Vector3f m_MaxExtents;	//Top Right Corner
	};
}