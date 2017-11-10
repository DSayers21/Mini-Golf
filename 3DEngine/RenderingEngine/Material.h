#pragma once

#include "Texture.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class Material
	{
	public:
		Material(Texture texture, Vector3f colour);
		Material(Texture texture, Vector3f colour, float SpecularIntensity, float SpecularExponent);
		~Material();

		//Getters
		inline Texture* GetTexture() { return &m_Texture; }
		inline Vector3f* GetColour() { return &m_Colour; }
		inline float GetSpecularIntensity() { return m_SpecularIntensity; }
		inline float GetSpecularExponent() { return m_SpecularExponent; }
		//Setters
		inline void SetTexture(Texture texture) { m_Texture = texture; }
		inline void SetColour(Vector3f colour) { m_Colour = colour; }
		inline void SetSpecularIntensity(float SpecularIntensity) { m_SpecularIntensity = SpecularIntensity; }
		inline void SetSpecularExponent(float SpecularExponent) { m_SpecularExponent = SpecularExponent; }

	private:
		Texture m_Texture;
		Vector3f m_Colour;
		float m_SpecularIntensity;  //How intense the reflection is
		float m_SpecularExponent;   //How wide the reflection is
	};
}
