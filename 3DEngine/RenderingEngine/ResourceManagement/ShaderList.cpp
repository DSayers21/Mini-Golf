//Includes
#include "ShaderList.h"

namespace D3DEngine
{
	ShaderList::ShaderList()
	{
		//Init shader map
		LoadedShaders = std::map<std::string, ShaderResource*>();
	}


	ShaderList::~ShaderList()
	{
		//Display message
		std::cerr << "Destructor: Shader List" << std::endl;
	}

	ShaderResource* ShaderList::GetShader(const std::string& Name)
	{
		//Try to find the shader in the map
		std::map<std::string, ShaderResource*>::const_iterator it = LoadedShaders.find(Name);
		if (it != LoadedShaders.end())	//If found then return the shader resource
			return it->second;
		return nullptr; //Else return a nullptr
	}

	void ShaderList::AddShader(const std::string& Name, ShaderResource* shaderResource)
	{
		//Insert the shader resource into the map with a key of name
		LoadedShaders.insert(std::pair<std::string, ShaderResource*>(Name, shaderResource));
	}

	void ShaderList::RemoveShader(const std::string& Name)
	{
		//Loop through all the elements in the map
		for (std::map<std::string, ShaderResource*>::iterator it = LoadedShaders.begin(); it != LoadedShaders.end();)
		{
			//If the key matches the passed name value
			if ((it->first) == Name)
			{
				//Delete the map element
				delete it->second;
				it = LoadedShaders.erase(it);
			}
			else //Else increment the iterator
				it++;
		}
	}
}