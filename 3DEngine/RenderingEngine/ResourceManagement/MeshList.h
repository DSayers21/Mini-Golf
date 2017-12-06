#pragma once

#include <map>
#include "MeshResource.h"

namespace D3DEngine
{
	class MeshList
	{
	public:
		MeshList();
		~MeshList();

		MeshResource* GetModel(std::string Name);
		void AddModel(std::string Name, MeshResource* meshResource);
		void RemoveModel(std::string Name);
	private:
		std::map<std::string, MeshResource*> LoadedModels;
	};
}