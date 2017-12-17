#include "ShaderList.h"

namespace D3DEngine
{
	ShaderList::ShaderList()
	{
		LoadedShaders = std::map<std::string, ShaderResource*>();
	}


	ShaderList::~ShaderList()
	{
		std::cerr << "Destructor: Shader List" << std::endl;
		/*for (std::map<std::string, ShaderResource*>::iterator it = LoadedShaders.begin(); it != LoadedShaders.end();)
		{
			delete it->second;
			it++;
		}

		LoadedShaders.clear();*/
	}

	ShaderResource* ShaderList::GetShader(std::string Name)
	{
		std::map<std::string, ShaderResource*>::const_iterator it = LoadedShaders.find(Name);
		if (it != LoadedShaders.end())
			return it->second;
		return nullptr;
	}

	void ShaderList::AddShader(std::string Name, ShaderResource* shaderResource)
	{
		LoadedShaders.insert(std::pair<std::string, ShaderResource*>(Name, shaderResource));
	}

	void ShaderList::RemoveShader(std::string Name)
	{
		for (std::map<std::string, ShaderResource*>::iterator it = LoadedShaders.begin(); it != LoadedShaders.end();)
		{
			if ((it->first) == Name)
			{
				delete it->second;
				it = LoadedShaders.erase(it);
			}
			else
				it++;
		}
	}
}