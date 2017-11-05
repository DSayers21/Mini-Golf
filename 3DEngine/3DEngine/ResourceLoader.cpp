#include "ResourceLoader.h"

namespace D3DEngine
{
	std::string ResourceLoader::LoadShader(const std::string& fileName)
	{
		std::ifstream File;
		File.open(("./Shaders/" + fileName).c_str());

		std::string Output;
		std::string Line;

		if (File.is_open())
		{
			while (File.good())
			{
				getline(File, Line);

				if (Line.find("#include") == std::string::npos)
					Output.append(Line + "\n");
				else
				{
					std::string includeFileName = Util::Split(Line, ' ')[1];
					includeFileName = includeFileName.substr(1, includeFileName.length() - 2);

					std::string toAppend = LoadShader(includeFileName);
					Output.append(toAppend + "\n");
				}
			}
		}
		else
		{
			std::cerr << "Unable to load shader: " << fileName << std::endl;
		}

		return Output;
	};
}