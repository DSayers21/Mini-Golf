#include "Material.h"

namespace D3DEngine
{
	Material::Material(Texture texture, Vector3f colour) : m_Texture(texture), m_Colour(colour)
	{
		*this = Material(texture, colour, 2, 8);
	}

	Material::Material(Texture texture, Vector3f colour, float SpecularIntensity, float SpecularExponent)
	{
		m_Texture = texture;
		m_Colour = colour;
		m_SpecularIntensity = SpecularIntensity;
		m_SpecularExponent = SpecularExponent;
	}

	Material::~Material()
	{
	}
}