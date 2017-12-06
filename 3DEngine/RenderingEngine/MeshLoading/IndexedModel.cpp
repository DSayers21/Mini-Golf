#include "IndexedModel.h"

namespace D3DEngine
{
	IndexedModel::IndexedModel()
	{
		m_Positons = std::vector<Vector3f>();
		m_TexCoords = std::vector<Vector2f>();
		m_Normals = std::vector<Vector3f>();
		m_Indices = std::vector<int>();
	}

	IndexedModel::~IndexedModel()
	{
	}

	void IndexedModel::CalcNormals()
	{

		for (int i = 0; i < m_Indices.size(); i += 3)
		{
			int i0 = m_Indices[i];
			int i1 = m_Indices[i + 1];
			int i2 = m_Indices[i + 2];

			Vector3f a = m_Positons[i1];
			Vector3f b = m_Positons[i2];
			Vector3f c = m_Positons[i0];

			Vector3f Vertex1 = (a - c);
			Vertex1 = Vertex1.Normalise();
			Vector3f Vertex2 = (b - c);
			Vertex2 = Vertex2.Normalise();
			//Calc Normal
			Vector3f Normal = Vertex1.CrossProduct(Vertex2);
			//Normal = Normal.Normalise();
			m_Normals[i0].Set(Normal);
			m_Normals[i1].Set(Normal);
			m_Normals[i2].Set(Normal);
		}

		for (int i = 0; i < m_Normals.size(); i++)
		{
			Vector3f New = m_Normals[i];
			Vector3f NewN = New.Normalise();
			m_Normals[i].Set(NewN);
		}
	}
}