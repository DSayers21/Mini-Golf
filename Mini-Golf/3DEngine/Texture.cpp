#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

namespace D3DEngine
{
	Texture::Texture(const std::string& FileName)
	{
		int Width, Height, NumComponents;
		unsigned char* ImageData = stbi_load(FileName.c_str(), &Width, &Height, &NumComponents, 4);

		if (ImageData == NULL)
			std::cerr << "Texture Loading Failed for texture: " << FileName << std::endl;

		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Send Texture To GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);

		stbi_image_free(ImageData);
	}

	Texture::~Texture()
	{
		std::cerr << "Texture Deleted" << std::endl;
		glDeleteTextures(1, &m_Texture);
	}

	void Texture::Bind(unsigned int unit)
	{
		//Make Sure uint is between the values
		assert(unit >= 0 && unit <= 31);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
}