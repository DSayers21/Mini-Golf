//Includes
#include "MappedValues.h"

namespace D3DEngine
{
	MappedValues::MappedValues()
	{
		//Setup maps
		m_Vector3fHashMap = std::map<std::string, Vector3f>();
		m_FloatHashMap = std::map<std::string, float>();
	}

	MappedValues::~MappedValues()
	{
		//Empty
	}

	Vector3f MappedValues::GetVector3f(const std::string& Name)
	{
		//Find element in map
		std::map<std::string, Vector3f>::const_iterator it = m_Vector3fHashMap.find(Name);
		//If found element then return it
		if (it != m_Vector3fHashMap.end())
			return it->second; 
		//Return default vector3f
		return Vector3f(0,0,0);
	}

	float MappedValues::GetFloat(const std::string& Name)
	{
		//Find element in map
		std::map<std::string, float>::const_iterator it = m_FloatHashMap.find(Name);
		//If found element then return it
		if (it != m_FloatHashMap.end())
			return it->second;
		//Return default float
		return 0;
	}
}