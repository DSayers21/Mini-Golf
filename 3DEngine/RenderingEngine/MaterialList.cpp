#include "MaterialList.h"


namespace D3DEngine
{
	MaterialList::MaterialList()
	{
		m_MaterialList = std::map<std::string, Material*>();
	}

	MaterialList::~MaterialList()
	{
	}

	void MaterialList::AddMaterial(const std::string & name, Material * material)
	{
		m_MaterialList.insert(std::pair<std::string, Material*>(name, material));
	}

	bool MaterialList::IsLoaded(const std::string & name)
	{
		Material* Temp = m_MaterialList.find(name)->second;
		if(Temp == nullptr)
			return false;
		else 
			return true;
	}
}