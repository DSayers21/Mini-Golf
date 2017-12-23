//Includes
#include "Texture.h"

namespace D3DEngine
{
	//Set to basic value
	Texture* Texture::m_LastBind = 0;

	Texture::Texture(const std::string& FileName, GLenum TextureTarget, GLfloat Filter)
	{
		//Load the texture
		LoadTexture(FileName, TextureTarget, Filter);
	}

	Texture::~Texture()
	{
		//Delete the last bind
		delete m_LastBind;
	}

	void Texture::LoadTexture(const std::string& FileName, GLenum TextureTarget, GLfloat Filter)
	{
		//Prepare variables for texture
		int X, Y, NumComponents;
		//Load the texture
		unsigned char* ImageData = stbi_load((FileName).c_str(), &X, &Y, &NumComponents, 4);
		//Check if image data is null, if so then display message
		if (ImageData == NULL)
			std::cerr << "Unable to load texture: " << FileName << std::endl;
		//Init the texture
		InitTexture(X, Y, ImageData, TextureTarget, Filter);
		//Free the image data
		stbi_image_free(ImageData);
	}

	void Texture::InitTexture(int Width, int Height, unsigned char * Data, GLenum TextureTarget, GLfloat Filter)
	{
		//Set the texture target
		m_TextureTarget = TextureTarget;
		//Set free texture to true
		m_FreeTexture = true;
		//Check if there is data
		if (Width > 0 && Height > 0 && Data != 0)
		{
			//Generate the texture
			glGenTextures(1, &m_TextureID);
			//Bind the texture
			glBindTexture(TextureTarget, m_TextureID);
			//Setup the texture
			glTexParameterf(TextureTarget, GL_TEXTURE_MIN_FILTER, Filter);
			glTexParameterf(TextureTarget, GL_TEXTURE_MAG_FILTER, Filter);
			glTexImage2D(TextureTarget, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
		}
		else //Else set textureID to 0
			m_TextureID = 0; 
	}

	void Texture::Bind(const int& TextureUnit)
	{
		//Set the active texture
		glActiveTexture(GL_TEXTURE0 + TextureUnit);
		//Bind the texture
		glBindTexture(m_TextureTarget, m_TextureID);
	}
}