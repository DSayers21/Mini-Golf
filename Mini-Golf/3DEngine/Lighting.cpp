#include "Lighting.h"



Lighting::Lighting()
{
}


Lighting::~Lighting()
{
}

void Lighting::InitLights(void)
{
	//SetUp Values
	SetMatSpecular(0.0, 1.0, 1.0, 1.0);
	SetMatShininess(20.0);
	SetLightPosition(1.0, 1.0, 1.0, 0.0);
	SetClearColour(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, m_MatShininess);
	glLightfv(GL_LIGHT0, GL_POSITION, m_LightPosition);
	glLightfv(GL_LIGHT1, GL_AMBIENT, m_LightAmbient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

void Lighting::SetGLFloat(GLfloat* ArrayToSet, GLfloat A, GLfloat B, GLfloat C, GLfloat D)
{
	ArrayToSet[0] = A;
	ArrayToSet[1] = B;
	ArrayToSet[2] = C;
	ArrayToSet[3] = D;
}