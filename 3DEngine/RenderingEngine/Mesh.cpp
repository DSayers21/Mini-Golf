//Includes
#include "Mesh.h"

namespace D3DEngine
{
	Mesh::Mesh(const std::string& FileName, MeshList* meshList)
	{
		//Set name to the filename
		m_Name = FileName;
		//Set the mesh list to point at the mesh list passed in
		m_MeshList = meshList;
		//Get the mesh resource for this mesh
		m_Buffers = m_MeshList->GetModel(FileName);

		if (m_Buffers == nullptr) //If there is no mesh resource already, then load it
		{
			//Dispaly message
			std::cerr << "Loaded Mesh: " << FileName << std::endl;
			//Create new mesh resource
			m_Buffers = new MeshResource();
			//Load the mesh
			LoadMesh(FileName);
			//Add the mesh resource to the mesh list
			meshList->AddModel(FileName, m_Buffers);
		}
		else //If the mesh resource already exists, then add a reference to it
		{
			//Dispaly message
			std::cerr << "Cached Mesh: " << FileName << std::endl;
			m_Buffers->AddReference();	//Add reference
		}
	}

	Mesh::Mesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize)
	{
		//Create a mesh resource
		m_Buffers = new MeshResource();
		//Generate the mesh
		*this = Mesh(Vertices, VertSize, Indices, IndexSize, false);
	}

	Mesh::Mesh(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals)
	{
		//Create a mesh resource
		m_Buffers = new MeshResource();
		//Generate the mesh
		AddVertices(Vertices, VertSize, Indices, IndexSize, calcNormals);
	}

	Mesh::~Mesh()
	{
		//If there is a mesh resource
		if (m_Buffers != nullptr)
			if (m_Buffers->RemoveReference())     //Remove a reference, if no more references left then:
				m_MeshList->RemoveModel(m_Name);  //Remove the mesh resource
	}

	void Mesh::Draw()
	{
		//Enable the attrib arrays
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//Bind the buffer to the VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers->GetVBO());
		//Prepare the memory for the mesh
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);												//Vert
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)sizeof(Vector3f));						//Texture COORDs
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (GLvoid*)(sizeof(Vector3f) + sizeof(Vector2f)));  //Normals
		//Bind the IBO budder
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers->GetIBO());
		//Draw the mesh
		glDrawElements(GL_TRIANGLES, m_Buffers->GetINDEXSIZE(), GL_UNSIGNED_INT, 0);
		//Disable the attrib arrays
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	void Mesh::AddVertices(Vert* Vertices, int VertSize, int* Indices, int IndexSize, bool calcNormals)
	{
		//If calc normals is true, then calculate the normals for the mesh
		if (calcNormals)
			this->CalcNormals(Vertices, VertSize, Indices, IndexSize);

		//Set the size of index, and vert
		m_Buffers->SetINDEXSIZE(IndexSize);
		m_Buffers->SetVERTEXSIZE(VertSize);
		//Set the mesh resources vertices and indicies
		m_Buffers->SetVertices(Vertices);
		m_Buffers->SetIndices(Indices);
		//Bind the buffer data for the VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers->GetVBO());
		glBufferData(GL_ARRAY_BUFFER, m_Buffers->GetVERTEXSIZE() * sizeof(Vert), Vertices, GL_STATIC_DRAW);
		//Bind the buffer data for the IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers->GetIBO());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Buffers->GetINDEXSIZE() * sizeof(int), Indices, GL_STATIC_DRAW);
	}

	void Mesh::CalcNormals(Vert* Vertices, int VertSize, int* Indices, int IndexSize)
	{
		//Loop over all the indexs
		for (int i = 0; i < IndexSize; i += 3)
		{
			//Get indicies of triangle
			int i0 = Indices[i];		//Get first indices
			int i1 = Indices[i + 1];	//Get second indices
			int i2 = Indices[i + 2];	//Get third indices

			//Calculate both Vertexs
			Vector3f Vertex1 = Vector3f(Vertices[i1].GetPos() - Vertices[i0].GetPos()).Normalise();
			Vector3f Vertex2 = Vector3f(Vertices[i2].GetPos() - Vertices[i0].GetPos()).Normalise();

			//Calculate the Normal
			Vector3f Normal = Vertex1.CrossProduct(Vertex2);

			//Set the normals values
			Vertices[i0].SetNormal(Vertices[i0].GetNormal() + Normal);
			Vertices[i1].SetNormal(Vertices[i1].GetNormal() + Normal);
			Vertices[i2].SetNormal(Vertices[i2].GetNormal() + Normal);
		}
		//Loop over each vert, and set the normals
		for (int i = 0; i < VertSize; i++)
			Vertices[i].SetNormal(Vector3f(Vertices[i].GetNormal()).Normalise());
	}

	void Mesh::LoadMesh(const std::string& FileName)
	{
		//Load the OBJmodel
		OBJModel ObjModel(FileName);
		//Convert the OBJmodel into a indexed model
		IndexedModel Model = ObjModel.ToIndexedModel();
		//Calculate the normals for the indexed model
		Model.CalcNormals();						

		//Prepare the memory for the vert and index arrays
		Vert* Vertices = new Vert[Model.GetPositions().size()];
		int* Indices = new int[Model.GetIndices().size()];

		//Get amount of indexs in the indexed model
		unsigned int Size = Model.GetIndices().size();
		//Loop over all indexs
		for (int i = 0; i < Size; i++)
			Indices[i] = Model.GetIndices()[i]; //Set the index to the models index

		//Get the size of the vert positions
		Size = Model.GetPositions().size();

		//Get the positions, tex coords, and normals from the indexed model
		std::vector<Vector3f> TempPositions = Model.GetPositions();
		std::vector<Vector2f> TempTexCoords = Model.GetTexCoords();
		std::vector<Vector3f> TempNormals = Model.GetNormals();

		//Loop over all vert positions
		for (int i = 0; i < Model.GetPositions().size(); i++)
		{
			//Create a vert with the current i, position values from the lists. And put it into the vert list
			Vertices[i] = Vert(TempPositions[i], TempTexCoords[i], TempNormals[i]);
		}
		//Add all the verts to the mesh
		AddVertices(&Vertices[0], Model.GetPositions().size(), Indices, Model.GetIndices().size(), false);
	}
}