#pragma once

//Includes
#include "Texture.h"
#include "Vector3f.h"
#include <map>

namespace D3DEngine
{
	class Material
	{
	public:
		//Constructor
		Material();
		//Destructor
		~Material();

		//Add to HashMaps
		inline void Material::AddTexture(const std::string& Name, Texture * texture){ m_TextureHashMap.insert(std::pair<std::string, Texture*>(Name, texture)); }
		inline void Material::AddVector3f(const std::string& Name, Vector3f vector3f) { m_Vector3fHashMap.insert(std::pair<std::string, Vector3f>(Name, vector3f)); }
		inline void Material::AddFloat(const std::string& Name, float Float) { m_FloatHashMap.insert(std::pair<std::string, float>(Name, Float)); }

		//Get From HashMaps
		Texture* Material::GetTexture(const std::string& Name);
		Vector3f Material::GetVector3f(const std::string& Name);
		float Material::GetFloat(const std::string& Name);

	private:
		//Maps for the textures, the vectors and the floats
		std::map<std::string, Texture*> m_TextureHashMap;
		std::map<std::string, Vector3f> m_Vector3fHashMap;
		std::map<std::string, float> m_FloatHashMap;
	};
}
