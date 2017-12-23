#pragma once

//Includes
#include <map>
#include "MeshResource.h"

namespace D3DEngine
{
	class MeshList
	{
	public:
		//Constructor
		MeshList();
		//Destructor
		~MeshList();

		//Get model from mesh map
		MeshResource* GetModel(const std::string& Name);
		//Add model to mesh map
		void AddModel(const std::string& Name, MeshResource* meshResource);
		//Remove model from mesh map
		void RemoveModel(const std::string& Name);
	private:
		//Map representing all the loaded models
		std::map<std::string, MeshResource*> m_LoadedModels;
	};
}