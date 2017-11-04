#ifndef SHADER_H
#define SHADER_H

#include "Camera.h"
#include "Transform.h"
#include <string>
#include <GL/glew.h>
#include <glm\glm.hpp>

namespace D3DEngine
{
	class Shader
	{
	public:
		Shader();
		Shader(const std::string& FileName);
		~Shader();

		void Bind();
		void Update(const Transform& transform, const Camera& camera);

	private:
		enum
		{
			TRANSFORM_U,
			NUM_UNIFORMS
		};

		static const unsigned int m_NUM_SHADERS = 2;
		GLuint m_Program;
		GLuint m_Shaders[m_NUM_SHADERS];
		GLuint m_Uniforms[NUM_UNIFORMS];
	};
}
#endif //SHADER_H