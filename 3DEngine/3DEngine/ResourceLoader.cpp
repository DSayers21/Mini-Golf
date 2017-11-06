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
	}
	
	Mesh* ResourceLoader::LoadMesh(std::string FileName)
	{
		std::vector<std::string> SplitArray = Util::Split(FileName, '.');
		std::string Ext = SplitArray[SplitArray.size()-1];;

		if (Ext != "obj")
			std::cerr << "Error: File format not supported for mesh data: " << Ext << std::endl;

		//Change to Pointer stuff
		std::vector<Vert> Vertices;
		std::vector<int> Indices;

		std::ifstream File;
		File.open((FileName).c_str());

		std::string Output;
		std::string Line;

		if (File.is_open())
		{
			while (File.good())
			{
				getline(File, Line);

				std::vector<std::string> Tokens = Util::Split(Line, ' ');
				Tokens = Util::RemoveEmptyStrings(Tokens);
				//Skip empty lines and comments
				if ((Tokens.size() == 0) || (Tokens[0] == "#"))
					continue;
				else if (Tokens[0] == "v") //Vertex
					Vertices.push_back(Vector3f(::atof(Tokens[1].c_str()), ::atof(Tokens[2].c_str()), ::atof(Tokens[3].c_str())));
				else if (Tokens[0] == "f") //Faces
				{
					Indices.push_back(::atof(Tokens[1].c_str())-1);
					Indices.push_back(::atof(Tokens[2].c_str())-1);
					Indices.push_back(::atof(Tokens[3].c_str())-1);
				}
			}
		}
		else
		{
			std::cerr << "Unable to load mesh: " << FileName << std::endl;
		}

		Mesh* ReturnMesh = new Mesh();

		Vert* VertexData = new Vert[Vertices.size()];

		for (int i = 0; i < Vertices.size(); i++)
			VertexData[i] = Vertices[i];

		int* IndexData = new int[Indices.size()];
		for (int i = 0; i < Indices.size(); i++)
			IndexData[i] = Indices[i];
		
		ReturnMesh->AddVertices(VertexData, Vertices.size(), IndexData, Indices.size());

		return ReturnMesh;
	}
}