#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include "stb_image.h"

namespace D3DEngine
{
	class Texture
	{
	public:
		Texture();
		Texture(const std::string& FileName, GLenum TextureTarget = GL_TEXTURE_2D, GLfloat Filter = GL_LINEAR);
		~Texture();

		Texture(Texture & texture);

		void Bind(GLenum TextureUnit = GL_TEXTURE0);

		void operator=(Texture & texture);

		//Setters
		//inline void SetTextureUnit(GLenum TextureUnit) { m_TextureUnit = TextureUnit; }

	private:
		
		void InitTexture(int Width, int Height, unsigned char* Data, GLenum TextureTarget, GLfloat Filter);

		void LoadTexture(std::string FileName, GLenum TextureTarget, GLfloat Filter);


		static Texture* m_LastBind;
		//GLenum m_TextureUnit = GL_TEXTURE0;
		GLenum m_TextureTarget;
		GLuint m_TextureID;
		bool m_FreeTexture;
	};
}