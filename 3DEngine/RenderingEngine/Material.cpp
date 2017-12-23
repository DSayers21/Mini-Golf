#include "Material.h"

namespace D3DEngine
{
	Material::Material()
	{
		//Init the maps
		m_TextureHashMap = std::map<std::string, Texture*>();
		m_Vector3fHashMap = std::map<std::string, Vector3f>();
		m_FloatHashMap = std::map<std::string, float>();
	}

	Material::~Material()
	{
		//Display message
		std::cerr << "Destructor: Material" << std::endl;
		//Delete all elemetns from the texture map
		for (std::map<std::string, Texture*>::iterator itr = m_TextureHashMap.begin(); itr != m_TextureHashMap.end(); itr++)
			delete itr->second;
		m_TextureHashMap.clear();
	}

	Texture* Material::GetTexture(const std::string& Name)
	{
		//Try to get a texture at key Name
		Texture* Return = m_TextureHashMap.find(Name)->second;
		//If Texture has a value then return it
		if (Return != nullptr)
			return Return;
		//If no texture, then create basic texture
		return new Texture("./Textures/Test.png");
	}

	Vector3f Material::GetVector3f(const std::string& Name)
	{
		//Try to find a vector at key Name
		std::map<std::string, Vector3f>::const_iterator it = m_Vector3fHashMap.find(Name);
		//If the key was found, then return the vector
		if (it != m_Vector3fHashMap.end())
			return it->second;
		//If the key was not found, then return basic vector
		return Vector3f(0, 0, 0);
	}

	float Material::GetFloat(const std::string& Name)
	{
		//Try to find a float at key Name
		std::map<std::string, float>::const_iterator it = m_FloatHashMap.find(Name);
		//If the key was found, then return the float
		if (it != m_FloatHashMap.end())
			return it->second;
		//If the key was not found, then return basic float
		return 0;
	}
}