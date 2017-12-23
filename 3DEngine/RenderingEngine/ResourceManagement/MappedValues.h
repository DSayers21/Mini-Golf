#pragma once

//Includes
#include "Vector3f.h"
#include <vector>
#include <map>

namespace D3DEngine
{
	class MappedValues
	{
	public:
		//Constructor
		MappedValues();
		//Destructors
		~MappedValues();

		//Getters
		Vector3f GetVector3f(const std::string& Name);
		float GetFloat(const std::string& Name);

		//Setters
		inline void AddVector3f(std::string Name, Vector3f vector3f) { m_Vector3fHashMap.insert(std::pair<std::string, Vector3f>(Name, vector3f)); }
		inline void AddFloat(std::string Name, float Float) { m_FloatHashMap.insert(std::pair<std::string, float>(Name, Float)); }

	protected:
		std::map<std::string, Vector3f> m_Vector3fHashMap;		//Vector3f Map
		std::map<std::string, float> m_FloatHashMap;			//Float Map
	};
}