#pragma once

//Includes
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#include "Vector3f.h"
#include "IndexedModel.h"
#include "OBJIndex.h"
#include "Util.h"

namespace D3DEngine
{
	class OBJModel
	{
	public:
		//Constructor
		OBJModel(const std::string& FileName);
		//Destructor
		~OBJModel();
		//Load the mesh at the filename
		void LoadMesh(const std::string& FileName);
		//Convert the OBJ model to being an indexed model
		IndexedModel ToIndexedModel();

	private:
		//Parse the string into a OBJ index
		OBJIndex ParseObjIndex(const std::string& Token);

		std::vector<Vector3f> m_Positons;		//Vector of vert positions for the mesh
		std::vector<Vector2f> m_TexCoords;		//Vector of texture coords for the mesh
		std::vector<Vector3f> m_Normals;		//Vector of normals for the mesh
		std::vector<OBJIndex> m_Indices;		//Vector of indicies for the mesh

		bool m_HasTexCoords;					//If the mesh being loaded has texture coords
		bool m_HasNormals;						//If the mesh being loaded has normals
	};
}