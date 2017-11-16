#include "MappedValues.h"

namespace D3DEngine
{
	MappedValues::MappedValues()
	{
		m_Vector3fHashMap = std::map<std::string, Vector3f>();
		m_FloatHashMap = std::map<std::string, float>();
	}


	MappedValues::~MappedValues()
	{
	}

	Vector3f MappedValues::GetVector3f(std::string Name)
	{
		std::map<std::string, Vector3f>::const_iterator it = m_Vector3fHashMap.find(Name);
		if (it != m_Vector3fHashMap.end())
			return it->second;

		return Vector3f(0, 0, 0);
	}

	float MappedValues::GetFloat(std::string Name)
	{
		std::map<std::string, float>::const_iterator it = m_FloatHashMap.find(Name);
		if (it != m_FloatHashMap.end())
			return it->second;

		return 0;
	}
}