#include "Mesh.h"

namespace D3DEngine
{
	Mesh::Mesh(std::string FileName, MeshList* meshList)
	{
		m_Name = FileName;
		m_MeshList = meshList;
		m_Buffers = m_MeshList->GetModel(FileName);

		if (m_Buffers == nullptr)
		{
			std::cerr << "Loaded Mesh: " << FileName << std::endl;
			m_Buffers = new MeshResource();
			LoadMesh(FileName);
			meshList->AddModel(FileName, m_Buffers);
		}
		else
		{
			std::cerr << "Cached Mesh: " << FileName << std::endl;
			m_Buffers->AddReference();
		}
	}

	Mesh::Mesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize)
	{
		m_Buffers = new MeshResource();
		*this = Mesh(Vertices, VertSize, Indices, IndexSize, false);
	}

	Mesh::Mesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals)
	{
		m_Buffers = new MeshResource();
		AddVertices(Vertices, VertSize, Indices, IndexSize, calcNormals);
	}

	Mesh::~Mesh()
	{
		if (m_Buffers->RemoveReference())
		{
			m_MeshList->RemoveModel(m_Name);
		}
	}

	void Mesh::Draw()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers->GetVBO());

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);						   //Vert
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)sizeof(Vector3f));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)(sizeof(Vector3f) + sizeof(Vector2f))); //Normals

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers->GetIBO());
		glDrawElements(GL_TRIANGLES, m_Buffers->GetINDEXSIZE(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

	}

	//Private

	void Mesh::AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals)
	{
		if (calcNormals)
			this->CalcNormals(Vertices, VertSize, Indices, IndexSize);

		m_Buffers->SetINDEXSIZE(IndexSize);
		m_Buffers->SetVERTEXSIZE(VertSize);

		m_Buffers->SetVertices(Vertices);
		m_Buffers->SetIndices(Indices);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers->GetVBO());
		glBufferData(GL_ARRAY_BUFFER, m_Buffers->GetVERTEXSIZE() * sizeof(Vert), Vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers->GetIBO());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Buffers->GetINDEXSIZE() * sizeof(int), Indices, GL_STATIC_DRAW);
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

		//std::vector<Vert> Vertices;	//Temp Buffer Vertex
		//std::vector<int> Indices = *Model.GetIndices();		//Temp Buffer Index
		
		Vert* Vertices = new Vert[Model.GetPositions()->size()];
		int* Indices = new int[Model.GetIndices()->size()];

		for (int i = 0; i < Model.GetIndices()->size(); i++)
			Indices[i] = Model.GetIndices()->at(i);




		for (int i = 0; i < Model.GetPositions()->size(); i++)
		{
			std::vector<Vector3f>* TempPositions = Model.GetPositions();
			std::vector<Vector2f>* TempTexCoords = Model.GetTexCoords();
			std::vector<Vector3f>* TempNormals = Model.GetNormals();

			Vector3f Testyas = TempPositions->at(i);
			Vert CurVert(TempPositions->at(i), TempTexCoords->at(i), TempNormals->at(i));
			Vertices[i] = CurVert;
		}

		AddVertices(&Vertices[0], Model.GetPositions()->size(), Indices, Model.GetIndices()->size(), false);
	}
}