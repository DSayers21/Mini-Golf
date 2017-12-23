//Includes
#include "OBJModel.h"

namespace D3DEngine
{
	OBJModel::OBJModel(const std::string& FileName)
	{
		//Setup variables to defaults
		m_Positons = std::vector<Vector3f>();
		m_TexCoords = std::vector<Vector2f>();
		m_Normals = std::vector<Vector3f>();
		m_Indices = std::vector<OBJIndex>();
		m_HasTexCoords = false;
		m_HasNormals = false;

		//Load the mesh being passed in
		LoadMesh(FileName);
	}

	OBJModel::~OBJModel()
	{
		//Empty
	}

	void OBJModel::LoadMesh(const std::string& FileName)
	{
		//Split the filename to get the filename and extension seperate
		std::vector<std::string> SplitArray = Util::Split(FileName, '.');
		std::string Ext = SplitArray[SplitArray.size() - 1];;	//Get the file extension

		if (Ext != "obj")	//Check if the extension is correct
			std::cerr << "Error: File format not supported for mesh data: " << Ext << std::endl;

		//Ready ifstream
		std::ifstream File;
		File.open((FileName).c_str()); //Open file

		//Current Line
		std::string Line;

		//If file is open
		if (File.is_open())
		{
			//While the file still has lines left to process
			while (File.good())
			{
				getline(File, Line);	//Get the current line
				//Split the current line based on ' ' space
				std::vector<std::string> Tokens = Util::Split(Line, ' ');
				Tokens = Util::RemoveEmptyStrings(Tokens); //Remove all empty strings from the list
				//Skip empty lines and comments
				if ((Tokens.size() == 0) || (Tokens[0] == "#"))
					continue;
				else if (Tokens[0] == "v") //If Vertex data, store to positions
					m_Positons.push_back(Vector3f(::atof(Tokens[1].c_str()), ::atof(Tokens[2].c_str()), ::atof(Tokens[3].c_str())));
				else if (Tokens[0] == "f") //If Faces, then store to indicies
				{
					//Triangulate (incase the verts are in quad format instead of triangle)
					for (int i = 0; i < Tokens.size() - 3; i++)
					{
						m_Indices.push_back(ParseObjIndex(Tokens[1]));
						m_Indices.push_back(ParseObjIndex(Tokens[2 + i]));
						m_Indices.push_back(ParseObjIndex(Tokens[3 + i]));
					}
				}
				else if (Tokens[0] == "vt") //If Vertex Texture COORD then store to tex coords
					m_TexCoords.push_back(Vector2f(::atof(Tokens[1].c_str()), ::atof(Tokens[2].c_str())));
				else if (Tokens[0] == "vn") //If Vertex Normal then store to normals
					m_Normals.push_back(Vector3f(::atof(Tokens[1].c_str()), ::atof(Tokens[2].c_str()), ::atof(Tokens[3].c_str())));
			}
		}
		else //File could not open, so display message
			std::cerr << "Unable to load mesh: " << FileName << std::endl;
	}

	IndexedModel OBJModel::ToIndexedModel()
	{
		IndexedModel Result;		//Holds the indexed model to be returned
		IndexedModel NormalResult;	//Holds the normals

		//Create maps for index map, normal map, and index map. To ensure elements are added once and for fast access
		std::map<OBJIndex, int> ResultIndexMap = std::map<OBJIndex, int>();
		std::map<int, int> NormalIndexMap = std::map<int, int>();
		std::map<int, int> IndexMap = std::map<int, int>();
		//Get the size of indicies
		unsigned int Size = m_Indices.size();
		//For each indicies loop
		for (int i = 0; i < Size; i++)
		{
			OBJIndex CurrentIndex = m_Indices[i];																	//Get Current index
			Vector3f CurrentPosition = m_Positons[CurrentIndex.VertexIndex];										//Get Current Position
			Vector2f CurrentTexCoord = (m_HasTexCoords) ? m_TexCoords[CurrentIndex.TexCoordIndex] : Vector2f(0, 0);	//Assign Tex Coord
			Vector3f CurrentNormal = (m_HasNormals) ? m_Normals[CurrentIndex.NormalIndex] : Vector3f(0, 0, 0);		//Assign Normal
			
			//Init ModelVertIndex
			int ModelVertIndex = -1;
			
			//Find any vertex with same index as current
			std::map<OBJIndex, int>::const_iterator it = ResultIndexMap.find(CurrentIndex);
			if (it != ResultIndexMap.end())
				ModelVertIndex = it->second;

			if (ModelVertIndex == -1)	//No pre exisitng point
			{
				//Get the size of positions
				ModelVertIndex = Result.GetPositions().size();
				ResultIndexMap.insert(std::pair<OBJIndex, int>(CurrentIndex, ModelVertIndex));

				//Add All Data to Indexed Model
				Result.GetPositions().push_back(CurrentPosition);
				Result.GetTexCoords().push_back(CurrentTexCoord);
				Result.GetNormals().push_back(CurrentNormal);
			}
			//Init ModelNormalIndex
			int ModelNormalIndex = -1;
			//Find any normal with same index as current
			std::map<int, int>::const_iterator it2 = NormalIndexMap.find(CurrentIndex.VertexIndex);
			if (it2 != NormalIndexMap.end())
				ModelNormalIndex = it2->second;

			if (ModelNormalIndex == -1)	//No pre exisitng point
			{
				//Get the size of normals
				ModelNormalIndex = NormalResult.GetPositions().size();
				NormalIndexMap.insert(std::pair<int, int>(CurrentIndex.VertexIndex, ModelNormalIndex));

				//Add All Data to Indexed Model
				NormalResult.GetPositions().push_back(CurrentPosition);
				NormalResult.GetTexCoords().push_back(CurrentTexCoord);
				NormalResult.GetNormals().push_back(CurrentNormal);
			}
			//Add indexs to list
			Result.GetIndices().push_back(ModelVertIndex);
			NormalResult.GetIndices().push_back(ModelNormalIndex);
			IndexMap.insert(std::pair<int, int>(ModelVertIndex, ModelNormalIndex));	//Insert index to map
		}

		if (!m_HasNormals)	//If the mesh loaded does not have normals
		{
			//Calculate normals
			NormalResult.CalcNormals();
			//Get amount of normals
			unsigned int Size = Result.GetNormals().size();
			//Loop for each normal
			for (int i = 0; i < Size; i++)
				Result.GetNormals()[i].Set(NormalResult.GetNormals()[IndexMap.find(i)->second]);	//Store the normal in Result
		}
		//Return the generated index model
		return Result;
	}

	OBJIndex OBJModel::ParseObjIndex(const std::string& Token)
	{
		//Prepare return object
		OBJIndex Result;
		//Split the string based on '/' 
		std::vector<std::string> Values = Util::Split(Token, '/');

		//Add Data
		Result.VertexIndex = ::atof(Values[0].c_str()) - 1;

		//Check if the list is greater than 1
		if (Values.size() > 1)
		{
			m_HasTexCoords = true;	//It has texture coordinates
			//Add Data
			Result.TexCoordIndex = ::atof(Values[1].c_str()) - 1;

			//Check if the list is greater than 2
			if (Values.size() > 2)
			{
				m_HasNormals = true; //It has normals
				//Add Data
				Result.NormalIndex = ::atof(Values[2].c_str()) - 1;
			}
		}
		//Return the OBJIndex object
		return Result;
	}
}