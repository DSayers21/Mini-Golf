#pragma once

#include <iostream>
#include <GL/glew.h>

namespace D3DEngine
{
	class ShaderResource
	{
	public:
		ShaderResource();
		~ShaderResource();

		inline void AddReference() { m_RefCount++; }
		inline bool RemoveReference() { m_RefCount--; return m_RefCount == 0; }

		//Getters
		inline int GetProgram() { return m_Program; }
		//Setters
		inline void SetProgram(int Program) { m_Program = Program; }
	private:
		int m_Program;
		int m_RefCount = 0;
	};
}