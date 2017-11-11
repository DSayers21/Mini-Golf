#pragma once
#include "BaseLight.h"
#include "Attenuation.h"
#include "Vector3f.h"

#include "GameComponent.h"

namespace D3DEngine
{
	class PointLight : public GameComponent
	{
	public:
		PointLight();
		PointLight(BaseLight& baseLight, Attenuation& attenuation, Vector3f& Position, float Range);
		~PointLight();

		//Getters
		inline BaseLight GetBaseLight() { return m_BaseLight; }
		inline Attenuation GetAttenuation() { return m_Attenuation; }
		inline Vector3f GetPosition() { return m_Position; }
		inline float GetRange() { return m_Range; }
		//Setters
		inline void SetBaseLight(BaseLight& baseLight) { m_BaseLight = baseLight; }
		inline void SetAttenuation(Attenuation& attenuation) { m_Attenuation = attenuation; }
		inline void SetPosition(Vector3f& vector3f) { m_Position = vector3f; }
		inline void SetRange(float& Range) { m_Range = Range; }

		void AddToRenderingEngine(RenderEngine * renderEngine);

	private:
		BaseLight m_BaseLight;
		Attenuation m_Attenuation;
		Vector3f m_Position;
		float m_Range;
	};
}