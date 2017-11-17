#include "IntersectData.h"

namespace D3DEngine
{
	IntersectData::IntersectData(const bool DoesIntersect, const float Distance) : 
		m_DoesIntersect(DoesIntersect), m_Distance(Distance)
	{
	}


	IntersectData::~IntersectData()
	{
	}
}