#include "OBJModel.h"

namespace D3DEngine
{
	OBJModel::OBJModel(std::string FileName)
	{
		m_Positons = std::vector<Vector3f>();
		m_TexCoords = std::vector<Vector2f>();
		m_Normals = std::vector<Vector3f>();
		m_Indices = std::vector<OBJIndex>();
		m_HasTexCoords = false;
		m_HasNormals = false;

		LoadMesh(FileName);
	}

	OBJModel::~OBJModel()
	{
	}

	void OBJModel::LoadMesh(std::string FileName)
	{
		std::vector<std::string> SplitArray = Util::Split(FileName, '.');
		std::string Ext = SplitArray[SplitArray.size() - 1];;

		if (Ext != "obj")
			std::cerr << "Error: File format not supported for mesh data: " << Ext << std::endl;

		//Change to Pointer stuff

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
					m_Positons.push_back(Vector3f(::atof(Tokens[1].c_str()), ::atof(Tokens[2].c_str()), ::atof(Tokens[3].c_str())));
				else if (Tokens[0] == "f") //Faces
				{
					//Triangulate
					for (int i = 0; i < Tokens.size() - 3; i++)
					{
						m_Indices.push_back(ParseObjIndex(Tokens[1]));
						m_Indices.push_back(ParseObjIndex(Tokens[2 + i]));
						m_Indices.push_back(ParseObjIndex(Tokens[3 + i]));
					}
				}
				else if (Tokens[0] == "vt") //Vertex Texture COORD
					m_TexCoords.push_back(Vector2f(::atof(Tokens[1].c_str()), ::atof(Tokens[2].c_str())));
				else if (Tokens[0] == "vn") //Vertex Normal
					m_Normals.push_back(Vector3f(::atof(Tokens[1].c_str()), ::atof(Tokens[2].c_str()), ::atof(Tokens[3].c_str())));
			}
		}
		else
			std::cerr << "Unable to load mesh: " << FileName << std::endl;
	}

	IndexedModel* OBJModel::ToIndexedModel()
	{
		IndexedModel Result;
		std::map<int, int> IndexMap = std::map<int, int>();
		int CurrentVertexIndex = 0;
		for (int i = 0; i < m_Indices.size(); i++)
		{
			OBJIndex CurrentIndex = m_Indices[i];															//Get Current index
			Vector3f CurrentPosition = m_Positons[CurrentIndex.VertexIndex];								//Get Current Position
			Vector2f CurrentTexCoord;
			Vector3f CurrentNormal;

			CurrentTexCoord = (m_HasTexCoords) ? m_TexCoords[CurrentIndex.TexCoordIndex] : Vector2f(0, 0);	//Assign Tex Coord
			CurrentNormal = (m_HasNormals) ? m_Normals[CurrentIndex.NormalIndex] : Vector3f(0, 0, 0);		//Assign Normal
			
			int PrevVertIndex = -1;
			for (int j = 0; j < i; j++)
			{
				OBJIndex OldIndex = m_Indices[j];

				if ((CurrentIndex.VertexIndex == OldIndex.VertexIndex)
					&& (CurrentIndex.TexCoordIndex == OldIndex.TexCoordIndex)
					&& (CurrentIndex.NormalIndex == OldIndex.NormalIndex))
				{
					//Pre existing point!
					PrevVertIndex = j;
					break;
				}
			}
			if (PrevVertIndex == -1)	//No pre exisitng point
			{
				IndexMap.insert(std::pair<int, int>(i, CurrentVertexIndex));

				//Add All Data to Indexed Model
				Result.GetPositions()->push_back(CurrentPosition);
				Result.GetTexCoords()->push_back(CurrentTexCoord);
				Result.GetNormals()->push_back(CurrentNormal);
				Result.GetIndices()->push_back(CurrentVertexIndex);
				CurrentVertexIndex++;
			}
			else						//Pre exisitng point
				Result.GetIndices()->push_back(IndexMap.find(PrevVertIndex)->second);
		}

		return &Result;
	}

	OBJIndex OBJModel::ParseObjIndex(std::string Token)
	{
		OBJIndex Result;

		std::vector<std::string> Values = Util::Split(Token, '/');

		//Add Data
		Result.VertexIndex = ::atof(Values[0].c_str()) - 1;

		if (Values.size() > 1)
		{
			m_HasTexCoords = true;
			//Add Data
			Result.TexCoordIndex = ::atof(Values[1].c_str()) - 1;

			if (Values.size() > 2)
			{
				//Add Data
				Result.NormalIndex = ::atof(Values[2].c_str()) - 1;
				m_HasNormals = true;
			}
		}
		return Result;
	}
}