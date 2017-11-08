#include "Material.h"

namespace D3DEngine
{
	Material::Material(Texture texture, Vector3f colour) : m_Texture(texture), m_Colour(colour)
	{
	}

	Material::~Material()
	{
	}
}