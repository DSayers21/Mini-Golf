#pragma once

#include <glut.h>

namespace D3DEngine
{
	class Lighting
	{
	public:
		Lighting();
		~Lighting();

		void InitLights(void);

		//Setters
		void SetMatSpecular(GLfloat A, GLfloat B, GLfloat C, GLfloat D) { SetGLFloat(m_MatSpecular, A, B, C, D); }
		void SetLightPosition(GLfloat A, GLfloat B, GLfloat C, GLfloat D) { SetGLFloat(m_LightPosition, A, B, C, D); }
		void SetClearColour(GLfloat A, GLfloat B, GLfloat C, GLfloat D) { glClearColor(A, B, C, D); }
		void SetLightAmbient(GLfloat A, GLfloat B, GLfloat C, GLfloat D) { SetGLFloat(m_LightAmbient, A, B, C, D); }

		void SetMatShininess(GLfloat MatShininess) { m_MatShininess[0] = MatShininess; };

	private:

		void SetGLFloat(GLfloat* ArrayToSet, GLfloat A, GLfloat B, GLfloat C, GLfloat D);

		GLfloat m_MatSpecular[4] = { 0.0, 1.0, 1.0, 1.0 };
		GLfloat m_MatShininess[1] = { 20.0 };
		GLfloat m_LightPosition[4] = { 1.0, 1.0, 1.0, 0.0 };
		GLfloat m_LightAmbient[4] = { 0.25, 0.25, 0.25, 1.0 };
	};
}