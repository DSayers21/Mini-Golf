#pragma once

#include "Vector3f.h"
#include "GameComponent.h"
#include "Attenuation.h"

namespace D3DEngine
{
	class BaseLight : public GameComponent
	{
	public:
		BaseLight();
		BaseLight(Vector3f colour, float intensity);
		~BaseLight();

		//Getters
		inline Vector3f GetColour() { return m_Colour; }
		inline float GetIntensity() { return m_Intensity; }
		inline Shader* GetShader() { return m_Shader; }
		//Setters
		inline void SetColour(Vector3f colour) { m_Colour = colour; }
		inline void SetIntensity(float intensity) { m_Intensity = intensity; }
		inline void SetShader(Shader* shader) { m_Shader = shader; }

		void AddToRenderingEngine(RenderEngine * renderEngine);

		//Getters
		inline Attenuation GetAttenuation() { return m_Attenuation; }
		inline Vector3f GetPosition() { return m_Position; }
		inline float GetRange() { return m_Range; }
		Vector3f GetDirection() { return m_Direction; }
		inline float& GetCutoff() { return m_Cutoff; }
		//Setters
		void SetDirection(Vector3f direction) { m_Direction = direction; }
		inline void SetAttenuation(Attenuation& attenuation) { m_Attenuation = attenuation; }
		inline void SetPosition(Vector3f& vector3f) { m_Position = vector3f; }
		inline void SetRange(float& Range) { m_Range = Range; }
		inline void SetCutoff(float cutoff) { m_Cutoff = cutoff; }
	protected:
		Shader* m_Shader;
		Vector3f m_Colour;
		float m_Intensity;
		Vector3f m_Direction;
		//Point Extras
		Attenuation m_Attenuation;
		Vector3f m_Position;
		float m_Range;
		//Spot Extras
		float m_Cutoff;
	};
}