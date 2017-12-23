//Includes
#include "TextureResource.h"

namespace D3DEngine
{
	TextureResource::TextureResource(GLuint ID, GLenum TextureTarget)
	{
		//Set texture ID to ID
		m_TextureID = ID;
		//Set reference counter to 1
		m_RefCount = 1;
	}

	TextureResource::~TextureResource()
	{
		//If textureID is not 0, then delete the textures
		if (m_TextureID)
			glDeleteTextures(1, &m_TextureID);
	}
}