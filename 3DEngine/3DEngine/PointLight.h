#pragma once
#include "BaseLight.h"
#include "Attenuation.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class PointLight
	{
	public:
		PointLight();
		PointLight(BaseLight& baseLight, Attenuation& attenuation, Vector3f& Position);
		~PointLight();

		//Operators


		//Getters
		inline BaseLight GetBaseLight() { return m_BaseLight; }
		inline Attenuation GetAttenuation() { return m_Attenuation; }
		inline Vector3f GetPosition() { return m_Position; }
		//Setters
		inline void SetBaseLight(BaseLight& baseLight) { m_BaseLight = baseLight; }
		inline void SetAttenuation(Attenuation& attenuation) { m_Attenuation = attenuation; }
		inline void SetPosition(Vector3f& vector3f) { m_Position = vector3f; }

	private:
		BaseLight m_BaseLight;
		Attenuation m_Attenuation;
		Vector3f m_Position;
	};
}