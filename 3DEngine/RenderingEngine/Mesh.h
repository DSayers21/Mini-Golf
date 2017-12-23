#pragma once

//Includes
#include <GL/glew.h>
#include "Vert.h"
#include "Util.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "MeshLoading/OBJModel.h"
#include "ResourceManagement/MeshResource.h"
#include "ResourceManagement/MeshList.h"

namespace D3DEngine
{
	class Mesh
	{
	public:
		//Constructors
		Mesh(const std::string& FileName, MeshList* meshList);
		Mesh(Vert * Vertices, int VertSize, int * Indices, int IndexSize);
		Mesh(Vert * Vertices, int VertSize, int * Indices, int IndexSize, bool calcNormals);
		//Destructor
		~Mesh();
		
		//Draw the mesh
		void Draw();

		//Getters
		inline Vert* GetVertices() { return m_Buffers->GetVertices(); }
		inline int* GetIndices() { return m_Buffers->GetIndices(); }

	private: 
		//Add vertices to the mesh
		void AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals);
		//Calculate normals of the mesh
		void CalcNormals(Vert* Vertices, int VertSize, int* Indices, int IndexSize);
		//Load a mesh
		void LoadMesh(const std::string& FileName);

		MeshResource* m_Buffers;  //Mesh Resource for the mesh
		MeshList* m_MeshList;	  //Pointer to the mesh list
		std::string m_Name;       //Name of the mesh
	};
}