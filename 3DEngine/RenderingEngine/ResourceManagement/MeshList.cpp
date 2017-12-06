#include "MeshList.h"

namespace D3DEngine
{
	MeshList::MeshList()
	{
		LoadedModels = std::map<std::string, MeshResource*>();
	}


	MeshList::~MeshList()
	{
	}

	MeshResource* MeshList::GetModel(std::string Name)
	{
		std::map<std::string, MeshResource*>::const_iterator it = LoadedModels.find(Name);
		if (it != LoadedModels.end())
		{
			return it->second;
		}
		return nullptr;
	}

	void MeshList::AddModel(std::string Name, MeshResource* meshResource)
	{
		LoadedModels.insert(std::pair<std::string, MeshResource*>(Name, meshResource));
	}

	void MeshList::RemoveModel(std::string Name)
	{
		for (std::map<std::string, MeshResource*>::iterator it = LoadedModels.begin(); it != LoadedModels.end();)
		{
			if ((it->first) == Name)
			{
				delete it->second;
				it = LoadedModels.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}