#include "TextureResource.h"

namespace D3DEngine
{
	TextureResource::TextureResource(GLuint ID, GLenum TextureTarget)
	{
		m_TextureID = ID;
		m_RefCount = 1;
	}


	TextureResource::~TextureResource()
	{
		if (m_TextureID)
			glDeleteTextures(1, &m_TextureID);
	}
}