#pragma once

namespace D3DEngine
{
	class IntersectData
	{
	public:
		IntersectData(const bool DoesIntersect, const float Distance);
		~IntersectData();

		//Getters
		inline bool GetDoesIntersect() const { return m_DoesIntersect; }
		inline float GetDistance() const { return m_Distance; }
	private:
		const bool m_DoesIntersect;
		const float m_Distance;
	};
}