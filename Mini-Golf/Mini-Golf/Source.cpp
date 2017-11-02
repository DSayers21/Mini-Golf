// Source.cpp : Defines the entry point for the console application.

//My Includes
#include <Vecmath.h>
#include <Window.h>
#include "MainGame.h"
//Includes
#include <glut.h>
#include <math.h>
#include <tchar.h>

//Defines
#define SIM_UPDATE_MS (20)

//Setup Pointer
MainGame* MGame;

//Glut Function Wrappers
void SpecKeyboardFunc(int key, int x, int y) { MGame->SpecKeyboardFunc(key, x, y); }
void SpecKeyboardUpFunc(int key, int x, int y) { MGame->SpecKeyboardUpFunc(key, x, y); }
void KeyboardFunc(unsigned char key, int x, int y) { MGame->KeyboardFunc(key, x, y); }
void KeyboardUpFunc(unsigned char key, int x, int y) { MGame->KeyboardUpFunc(key, x, y); }
void RenderScene(void) 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MGame->RenderScene();

	glFlush();
	glutSwapBuffers();
}
void ChangeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;
	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 0.2, 1000);
	glMatrixMode(GL_MODELVIEW);

	MGame->GetCamera()->LookAt();
}
void UpdateScene(int ms)
{
	MGame->UpdateScene(ms);
	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
	glutPostRedisplay();
}
//End - Glut Function Wrappers

int _tmain(int argc, _TCHAR* argv[])
{
	//Init Glut
	glutInit(&argc, ((char **)argv));

	//Create Window
	D3DEngine::Window MainWindow;
	MainWindow.Init("MSc Assignment : Mini Golf Game", 1000, 700);

	//Init Main Game
	MGame = new MainGame();

	//Setup Glut
	glutDisplayFunc(RenderScene);
	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(RenderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyboardUpFunc);
	glutSpecialFunc(SpecKeyboardFunc);
	glutSpecialUpFunc(SpecKeyboardUpFunc);
	//End - Setup Glut

	//Start Main Loop
	glutMainLoop();

	//Delete Main Game
	delete[] MGame;
}