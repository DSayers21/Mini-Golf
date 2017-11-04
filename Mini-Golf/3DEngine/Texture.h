#pragma once

#include <string>
#include <GL/glew.h>

namespace D3DEngine
{
	class Texture
	{
	public:
		Texture(){}
		Texture(const std::string& FileName);

		~Texture();

		void Bind(unsigned int unit);
	private:
		GLuint m_Texture;
	};
}