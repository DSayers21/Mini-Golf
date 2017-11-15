#include "Material.h"

namespace D3DEngine
{
	Material::Material()
	{
		m_TextureHashMap = std::map<std::string, Texture*>();
		m_Vector3fHashMap = std::map<std::string, Vector3f*>();
		m_FloatHashMap = std::map<std::string, float>();
	}

	Material::~Material()
	{
	}

	Texture* Material::GetTexture(std::string Name)
	{
		Texture* Return = m_TextureHashMap.find(Name)->second;

		if (Return != nullptr)
			return Return;

		return new Texture("./Textures/Test.png");
	}

	Vector3f * Material::GetVector3f(std::string Name)
	{
		std::map<std::string, Vector3f*>::const_iterator it = m_Vector3fHashMap.find(Name);
		if (it != m_Vector3fHashMap.end())
			return it->second;

		return new Vector3f(0, 0, 0);
	}

	float Material::GetFloat(std::string Name)
	{
		std::map<std::string, float>::const_iterator it = m_FloatHashMap.find(Name);
		if (it != m_FloatHashMap.end())
			return it->second;

		return 0;
	}
}