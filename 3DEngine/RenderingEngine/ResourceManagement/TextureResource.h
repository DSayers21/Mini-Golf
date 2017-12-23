#pragma once

//Includes
#include <GL/glew.h>

namespace D3DEngine
{
	class TextureResource
	{
	public:
		//Constructor
		TextureResource(GLuint ID, GLenum TextureTarget);
		//Destructor
		~TextureResource();
		//Add reference to the texture resource
		inline void AddReference() { m_RefCount++; }
		//Remove reference from the texture resource
		inline bool RemoveReference() { m_RefCount--; return m_RefCount == 0; }

		//Getters
		inline GLuint* GetID() { return &m_TextureID; }
		inline GLenum* GetTexTarget() { return &m_TextureTarget; }

		//Setters
		inline void SetID(GLuint TextureID) { m_TextureID = TextureID; }
		inline void SetTexTarget(GLenum TextureTarget) { m_TextureTarget = TextureTarget; }

	private:
		int m_RefCount = 0;			//Reference counter
		GLuint m_TextureID;			//TextureID
		GLenum m_TextureTarget;		//The texture target
	};
}