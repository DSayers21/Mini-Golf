#include "Material.h"

namespace D3DEngine
{
	Material::Material()
	{
		m_TextureHashMap = std::map<std::string, Texture*>();
		m_Vector3fHashMap = std::map<std::string, Vector3f>();
		m_FloatHashMap = std::map<std::string, float>();
	}

	Material::~Material()
	{
		std::cerr << "Destructor: Material" << std::endl;
		for (std::map<std::string, Texture*>::iterator itr = m_TextureHashMap.begin(); itr != m_TextureHashMap.end(); itr++)
		{
			delete itr->second;
		}
		m_TextureHashMap.clear();
	}

	Texture* Material::GetTexture(const std::string& Name)
	{
		Texture* Return = m_TextureHashMap.find(Name)->second;

		if (Return != nullptr)
			return Return;

		return new Texture("./Textures/Test.png");
	}

	Vector3f Material::GetVector3f(std::string Name)
	{
		std::map<std::string, Vector3f>::const_iterator it = m_Vector3fHashMap.find(Name);
		if (it != m_Vector3fHashMap.end())
			return it->second;

		return Vector3f(0, 0, 0);
	}

	float Material::GetFloat(std::string Name)
	{
		std::map<std::string, float>::const_iterator it = m_FloatHashMap.find(Name);
		if (it != m_FloatHashMap.end())
			return it->second;

		return 0;
	}
}