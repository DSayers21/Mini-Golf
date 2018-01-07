#pragma once

//Includes
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
		//Constructor
		Texture(const std::string& FileName, GLenum TextureTarget = GL_TEXTURE_2D, GLfloat Filter = GL_LINEAR);
		//Destructor
		~Texture();
		//Bind to the texture
		void Bind(const int& TextureUnit = 0);

	private:
		//Init the texture
		void InitTexture(int Width, int Height, unsigned char* Data, GLenum TextureTarget, GLfloat Filter);
		//Load the texture
		void LoadTexture(const std::string& FileName, GLenum TextureTarget, GLfloat Filter);


		static Texture* m_LastBind; //Last texture bound
		GLenum m_TextureTarget;		//The texture target
		GLuint m_TextureID;			//The texture IDs
		bool m_FreeTexture;			//Whether or not to free the texture
	};
}