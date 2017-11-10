#pragma once

#include "Vector3f.h"
namespace D3DEngine
{
	class BaseLight
	{
	public:
		BaseLight();
		BaseLight(Vector3f colour, float intensity);
		~BaseLight();

		//Getters
		Vector3f GetColour() { return m_Colour; }
		float GetIntensity() { return m_Intensity; }
		//Setters
		void SetColour(Vector3f colour) { m_Colour = colour; }
		void SetIntensity(float intensity) { m_Intensity = intensity; }

	private:
		Vector3f m_Colour;
		float m_Intensity;
	};
}