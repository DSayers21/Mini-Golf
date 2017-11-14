#include "Mesh.h"

namespace D3DEngine
{
	//LoadMesh(std::string FileName)
	Mesh::Mesh(std::string FileName)
	{
		InitMeshData();
		LoadMesh(FileName);
	}

	Mesh::Mesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize)
	{
	*this = Mesh(Vertices, VertSize, Indices, IndexSize, false);
	}

	Mesh::Mesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals)
	{
		InitMeshData();
		AddVertices(Vertices, VertSize, Indices, IndexSize, calcNormals);
	}

	Mesh::~Mesh()
	{
		if (m_VBO) glDeleteBuffers(1, &m_VBO);
		if (m_IBO) glDeleteBuffers(1, &m_IBO);
	}

	void Mesh::Draw()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);						   //Vert
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)sizeof(Vector3f));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)(sizeof(Vector3f) + sizeof(Vector2f))); //Normals

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glDrawElements(GL_TRIANGLES, m_IndicesSize, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

	}

	//Private
	void Mesh::InitMeshData()
	{
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);
		m_VertSize = 0;
		m_IndicesSize = 0;
	}

	void Mesh::AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals)
	{
		if (calcNormals)
			this->CalcNormals(Vertices, VertSize, Indices, IndexSize);

		m_VertSize = VertSize;
		m_IndicesSize = IndexSize;
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_VertSize * sizeof(Vert), Vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesSize * sizeof(int), Indices, GL_STATIC_DRAW);
	}

	void Mesh::CalcNormals(Vert* Vertices, int VertSize, int* Indices, int IndexSize)
	{

		std::vector<Vert> test;
		for (int i = 0; i < IndexSize; i += 3)
		{
			int i0 = Indices[i];
			int i1 = Indices[i + 1];
			int i2 = Indices[i + 2];

			Vector3f a = Vertices[i1].GetPos();
			Vector3f b = Vertices[i2].GetPos();
			Vector3f c = Vertices[i0].GetPos();

			Vector3f Vertex1 = (a - c);
			Vertex1 = Vertex1.Normalise();
			Vector3f Vertex2 = (b - c);
			Vertex2 = Vertex2.Normalise();
			//Calc Normal
			Vector3f Normal = Vertex1.CrossProduct(Vertex2);
			//Normal = Normal.Normalise();
			Vertices[i0].SetNormal(Vertices[i0].GetNormal() + Normal);
			Vertices[i1].SetNormal(Vertices[i1].GetNormal() + Normal);
			Vertices[i2].SetNormal(Vertices[i2].GetNormal() + Normal);
		}

		for (int i = 0; i < VertSize; i++)
		{
			Vector3f New = Vertices[i].GetNormal();
			Vector3f NewN = New.Normalise();
			Vertices[i].SetNormal(NewN);
		}
	}

	void Mesh::LoadMesh(std::string FileName)
	{
		OBJModel ObjModel(FileName);
		IndexedModel Model = *ObjModel.ToIndexedModel();
		Model.CalcNormals();								//Calculate Normals

		std::vector<Vert> Vertices;							//Temp Buffer Vertex
		std::vector<int> Indices = *Model.GetIndices();		//Temp Buffer Index

		for (int i = 0; i < Model.GetPositions()->size(); i++)
		{
			std::vector<Vector3f>* TempPositions = Model.GetPositions();
			std::vector<Vector2f>* TempTexCoords = Model.GetTexCoords();
			std::vector<Vector3f>* TempNormals = Model.GetNormals();

			Vector3f Testyas = TempPositions->at(i);
			Vert CurVert(TempPositions->at(i), TempTexCoords->at(i), TempNormals->at(i));
			Vertices.push_back(CurVert);
		}
		
		AddVertices(&Vertices[0], Vertices.size(), &Indices[0], Indices.size(), false);
	}
}