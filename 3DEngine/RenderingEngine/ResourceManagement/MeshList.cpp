#include "MeshList.h"

namespace D3DEngine
{
	MeshList::MeshList()
	{
		//Init loaded models map
		m_LoadedModels = std::map<std::string, MeshResource*>();
	}


	MeshList::~MeshList()
	{
		//Empty
	}

	MeshResource* MeshList::GetModel(const std::string& Name)
	{
		//Try to find the element in the map
		std::map<std::string, MeshResource*>::const_iterator it = m_LoadedModels.find(Name);
		//If found then return the mesh resource
		if (it != m_LoadedModels.end())
			return it->second;
		//If not found return a nullptr
		return nullptr;
	}

	void MeshList::AddModel(const std::string& Name, MeshResource* meshResource)
	{
		//Insert the mesh resource into the map, with key of name
		m_LoadedModels.insert(std::pair<std::string, MeshResource*>(Name, meshResource));
	}

	void MeshList::RemoveModel(const std::string& Name)
	{
		//Loop through the map of loaded models
		for (std::map<std::string, MeshResource*>::iterator it = m_LoadedModels.begin(); it != m_LoadedModels.end();)
		{
			if ((it->first) == Name) //If key equals the Name passed in
			{
				//Delete the map entry
				delete it->second;
				it = m_LoadedModels.erase(it);
			}
			else //Else iterate through the map
				it++;
		}
	}
}