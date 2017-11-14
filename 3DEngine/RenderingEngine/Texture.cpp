#include "Texture.h"
namespace D3DEngine
{
	Texture* Texture::m_LastBind = 0;

	Texture::Texture()
	{
	}

	Texture::Texture(const std::string& FileName, GLenum TextureTarget, GLfloat Filter)
	{
		int X, Y, NumComponents;
		unsigned char* ImageData = stbi_load((FileName).c_str(), &X, &Y, &NumComponents, 4);

		if (ImageData == NULL)
			std::cerr << "Unable to load texture: " << FileName << std::endl;

		InitTexture(X, Y, ImageData, TextureTarget, Filter);
		stbi_image_free(ImageData);
	}

	Texture::~Texture()
	{
		if (m_FreeTexture)
			glDeleteTextures(1, &m_TextureID);
	}

	Texture::Texture(Texture& texture)
	{
		m_TextureTarget = texture.m_TextureTarget;
		m_TextureID = texture.m_TextureID;
		m_FreeTexture = true;
		texture.m_FreeTexture = false;
	}

	void Texture::operator=(Texture& texture)
	{
		m_TextureTarget = texture.m_TextureTarget;
		m_TextureID = texture.m_TextureID;
		m_FreeTexture = true;
		texture.m_FreeTexture = false;
	}

	void Texture::InitTexture(int Width, int Height, unsigned char * Data, GLenum TextureTarget, GLfloat Filter)
	{
		m_TextureTarget = TextureTarget;
		m_FreeTexture = true;

		if (Width > 0 && Height > 0 && Data != 0)
		{
			glGenTextures(1, &m_TextureID);
			glTexParameterf(TextureTarget, GL_TEXTURE_MIN_FILTER, Filter);
			glTexParameterf(TextureTarget, GL_TEXTURE_MAG_FILTER, Filter);
			glTexImage2D(TextureTarget, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
		}
		else
		{
			m_TextureID = 0;
		}
	}

	void Texture::Bind(GLenum TextureUnit)
	{
		glActiveTexture(TextureUnit);
		glBindTexture(m_TextureTarget, m_TextureID);
	}
}