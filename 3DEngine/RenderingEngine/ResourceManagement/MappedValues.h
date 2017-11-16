#pragma once

#include "Vector3f.h"
#include <vector>
#include <map>

namespace D3DEngine
{
	class MappedValues
	{
	public:
		MappedValues();
		~MappedValues();

		//Getters
		Vector3f GetVector3f(std::string Name);
		float GetFloat(std::string Name);
		//Setters
		inline void AddVector3f(std::string Name, Vector3f vector3f) { m_Vector3fHashMap.insert(std::pair<std::string, Vector3f>(Name, vector3f)); }
		inline void AddFloat(std::string Name, float Float) { m_FloatHashMap.insert(std::pair<std::string, float>(Name, Float)); }

	protected:
		std::map<std::string, Vector3f> m_Vector3fHashMap;
		std::map<std::string, float> m_FloatHashMap;
	};
}