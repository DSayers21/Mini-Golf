#pragma once

#include <GL/glew.h>
#include "Vert.h"
#include "Util.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

namespace D3DEngine
{
	class Mesh
	{
	public:
		Mesh(std::string & const FileName);
		Mesh(Vert * Vertices, int VertSize, int * Indices, int IndexSize);
		Mesh(Vert * Vertices, int VertSize, int * Indices, int IndexSize, bool calcNormals);
		~Mesh();
		

		void Draw();
	private: 
		void InitMeshData();
		void AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals);
		void CalcNormals(Vert* Vertices, int VertSize, int* Indices, int IndexSize);
		void LoadMesh(std::string FileName);

		//VBO is a Pointer to the data
		unsigned int m_VBO; //Vertex Buffer Object
		unsigned int m_IBO; //Index Buffer Object
		int m_VertSize;
		int m_IndicesSize;
	};
}