#pragma once
#include "PointLight.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class SpotLight
	{
	public:
		SpotLight();
		SpotLight(PointLight pointLight, Vector3f direction, float cutoff);
		~SpotLight();

		//Getters
		inline PointLight& GetPointLight() { return m_PointLight; }
		inline Vector3f& GetDirection() { return m_Direction; }
		inline float& GetCutoff() { return m_Cutoff; }
		//Setters
		inline void SetPointLight(PointLight pointLight) { m_PointLight = pointLight; }
		inline void SetDirection(Vector3f direction) { m_Direction = direction.Normalise(); }
		inline void SetCutoff(float cutoff) { m_Cutoff = cutoff; }

	private:
		PointLight m_PointLight;
		Vector3f m_Direction;
		float m_Cutoff;
	};
}