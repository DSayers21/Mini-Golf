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

		for (int i = 0; i < VertSize; i ++)
		{
			Vector3f New = Vertices[i].GetNormal();
			Vector3f NewN = New.Normalise();
			Vertices[i].SetNormal(NewN);
		}
	}

	void Mesh::LoadMesh(std::string FileName)
	{
		std::vector<std::string> SplitArray = Util::Split(FileName, '.');
		std::string Ext = SplitArray[SplitArray.size() - 1];;

		OBJModel Test(FileName);

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
					Indices.push_back(::atof(Util::Split(Tokens[1], '/')[0].c_str()) - 1);
					Indices.push_back(::atof(Util::Split(Tokens[2], '/')[0].c_str()) - 1);
					Indices.push_back(::atof(Util::Split(Tokens[3], '/')[0].c_str()) - 1);

					if (Tokens.size() > 4)
					{
						Indices.push_back(::atof(Util::Split(Tokens[1], '/')[0].c_str()) - 1);
						Indices.push_back(::atof(Util::Split(Tokens[3], '/')[0].c_str()) - 1);
						Indices.push_back(::atof(Util::Split(Tokens[4], '/')[0].c_str()) - 1);
					}
				}
			}
		}
		else
			std::cerr << "Unable to load mesh: " << FileName << std::endl;

		Vert* VertexData = new Vert[Vertices.size()];

		for (int i = 0; i < Vertices.size(); i++)
			VertexData[i] = Vertices[i];

		int* IndexData = new int[Indices.size()];
		for (int i = 0; i < Indices.size(); i++)
			IndexData[i] = Indices[i];

		AddVertices(&Vertices[0], Vertices.size(), &Indices[0], Indices.size(), true);
	}
}