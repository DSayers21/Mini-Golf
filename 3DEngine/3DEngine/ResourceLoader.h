#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <Vector>

#include "Util.h"
#include "Mesh.h"

namespace D3DEngine
{
	class ResourceLoader
	{
	public:
		static std::string ResourceLoader::LoadShader(const std::string& FileName);
		static Mesh* LoadMesh(std::string FileName);
		static unsigned char * LoadTexture(std::string FileName);
	};
}