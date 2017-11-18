#include "IntersectData.h"

namespace D3DEngine
{
	IntersectData::IntersectData(const bool DoesIntersect, const Vector3f& Direction) :
		m_DoesIntersect(DoesIntersect), m_Direction(Direction)
	{
	}


	IntersectData::~IntersectData()
	{
	}
}