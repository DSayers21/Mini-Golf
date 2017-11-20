#pragma once

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
		Mesh(std::string FileName, MeshList* meshList);
		Mesh(Vert * Vertices, int VertSize, int * Indices, int IndexSize);
		Mesh(Vert * Vertices, int VertSize, int * Indices, int IndexSize, bool calcNormals);
		~Mesh();
		
		void Draw();

		//Getters
		inline Vert* GetVertices() {
			return m_Buffers->GetVertices();
		}
		inline int* GetIndices() { return m_Buffers->GetIndices(); }

	private: 
		void AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals);
		void CalcNormals(Vert* Vertices, int VertSize, int* Indices, int IndexSize);

		void LoadMesh(std::string FileName);

		MeshResource* m_Buffers;
		MeshList* m_MeshList;
		std::string m_Name;
	};
}