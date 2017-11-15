#pragma once
#include <GL/glew.h>

namespace D3DEngine
{
	class TextureResource
	{
	public:
		TextureResource(GLuint ID, GLenum TextureTarget);
		~TextureResource();

		inline void AddReference() { m_RefCount++; }
		inline bool RemoveReference() { m_RefCount--; return m_RefCount == 0; }

		//Getters
		inline GLuint* GetID() { return &m_TextureID; }
		inline GLenum* GetTexTarget() { return &m_TextureTarget; }
		//Setters
		inline void SetID(GLuint TextureID) { m_TextureID = TextureID; }
		inline void SetTexTarget(GLenum TextureTarget) { m_TextureTarget = TextureTarget; }
	private:
		int m_RefCount = 0;
		GLuint m_TextureID;
		GLenum m_TextureTarget;
	};
}