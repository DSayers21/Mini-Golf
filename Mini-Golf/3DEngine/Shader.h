#ifndef SHADER_H
#define SHADER_H

#include <string>

//#include <GL/glew.h>
#include <GL\glew.h>
namespace D3DEngine
{
	class Shader
	{
	public:
		Shader();
		Shader(const std::string& FileName);
		~Shader();

		Shader(const Shader& Other);
		void operator=(const Shader& Other);

		void Bind();

	private:
		static const unsigned int m_NUM_SHADERS = 2;
		GLuint m_Program;
		GLuint m_Shaders[m_NUM_SHADERS];
	};
}
#endif //SHADER_H