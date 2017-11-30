#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include "stb_image.h"
#include "ResourceManagement/TextureResource.h"

namespace D3DEngine
{
	class Texture
	{
	public:
		Texture(const std::string& FileName, GLenum TextureTarget = GL_TEXTURE_2D, GLfloat Filter = GL_LINEAR);
		~Texture();

		void Bind(const int& TextureUnit = 0);

	private:
		
		void InitTexture(int Width, int Height, unsigned char* Data, GLenum TextureTarget, GLfloat Filter);
		void LoadTexture(std::string FileName, GLenum TextureTarget, GLfloat Filter);


		static Texture* m_LastBind;
		GLenum m_TextureTarget;
		GLuint m_TextureID;
		bool m_FreeTexture;
	};
}