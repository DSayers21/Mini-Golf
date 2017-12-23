//Includes
#include "IndexedModel.h"

namespace D3DEngine
{
	IndexedModel::IndexedModel()
	{
		//Init Variables
		m_Positons = std::vector<Vector3f>();
		m_TexCoords = std::vector<Vector2f>();
		m_Normals = std::vector<Vector3f>();
		m_Indices = std::vector<int>();
	}

	IndexedModel::~IndexedModel()
	{
		//Empty
	}

	void IndexedModel::CalcNormals()
	{
		//Get amount of indices
		unsigned int Size = m_Indices.size();
		//Loop Over all indices
		for (int i = 0; i < Size; i += 3)
		{
			//Get indicies of triangle
			int i0 = m_Indices[i];		//Get first indices
			int i1 = m_Indices[i + 1];	//Get second indices
			int i2 = m_Indices[i + 2];	//Get third indices

			//Calculate both Vertexs
			Vector3f Vertex1 = Vector3f(m_Positons[i1] - m_Positons[i0]).Normalise();
			Vector3f Vertex2 = Vector3f(m_Positons[i2] - m_Positons[i0]).Normalise();

			//Calculate Normal
			Vector3f Normal = Vertex1.CrossProduct(Vertex2);

			//Set the normals values
			m_Normals[i0].Set(Normal);
			m_Normals[i1].Set(Normal);
			m_Normals[i2].Set(Normal);
		}
		//Get amount of normals
		Size = m_Normals.size();
		//Loop over all normals and normalise the normal
		for (int i = 0; i < Size; i++)
			m_Normals[i].Set(Vector3f(m_Normals[i]).Normalise());
	}
}