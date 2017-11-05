#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace D3DEngine
{
	struct OBJIndex
	{
		unsigned int m_VertexIndex;
		unsigned int m_UVIndex;
		unsigned int m_NormalIndex;

		bool operator<(const OBJIndex& R) const { return m_VertexIndex < R.m_VertexIndex; }
	};

	class IndexedModel
	{
	public:
		std::vector<glm::vec3> m_Positions;
		std::vector<glm::vec2> m_TexCoords;
		std::vector<glm::vec3> m_Normals;
		std::vector<unsigned int> m_Indices;

		void CalcNormals();
	};

	class OBJModel
	{
	public:
		std::vector<OBJIndex> m_OBJIndices;
		std::vector<glm::vec3> m_Vertices;
		std::vector<glm::vec2> m_UVs;
		std::vector<glm::vec3> m_Normals;
		bool m_HasUVs;
		bool m_HasNormals;

		OBJModel(const std::string& FileName);

		IndexedModel ToIndexedModel();
	private:
		unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& IndexLookup, const OBJIndex* CurrentIndex, const IndexedModel& Result);
		void CreateOBJFace(const std::string& Line);

		glm::vec2 ParseOBJVec2(const std::string& Line);
		glm::vec3 ParseOBJVec3(const std::string& Line);
		OBJIndex ParseOBJIndex(const std::string& Token, bool* HasUVs, bool* HasNormals);
	};
}