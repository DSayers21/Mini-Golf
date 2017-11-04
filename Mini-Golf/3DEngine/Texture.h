#pragma once

#include <string>
#include <GL/glew.h>
#include <glut.h>

namespace D3DEngine
{
	class Texture
	{
	public:
		Texture(const std::string& FileName);

		~Texture();

		void Bind(unsigned int unit);
	private:
		GLuint m_Texture;
	};
}