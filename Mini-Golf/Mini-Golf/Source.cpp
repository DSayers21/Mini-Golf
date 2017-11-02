// Pool Game.cpp : Defines the entry point for the console application.
#include "vecmath.h"

#include "Window.h"
#include "Lighting.h"
#include "Camera.h"
#include "MainGame.h"

#include <glut.h>
#include <math.h>
#include <tchar.h>

#define SIM_UPDATE_MS (20)


MainGame MGame;

//Glut Function Wrappers
void RenderScene(void) { MGame.RenderScene(); }
void SpecKeyboardFunc(int key, int x, int y) { MGame.SpecKeyboardFunc(key, x, y); }
void SpecKeyboardUpFunc(int key, int x, int y) { MGame.SpecKeyboardUpFunc(key, x, y); }
void KeyboardFunc(unsigned char key, int x, int y) { MGame.KeyboardFunc(key, x, y); }
void KeyboardUpFunc(unsigned char key, int x, int y) { MGame.KeyboardUpFunc(key, x, y); }
void ChangeSize(int w, int h) { MGame.ChangeSize(w, h); }
void UpdateScene(int ms)
{
	MGame.UpdateScene(ms);
	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
	glutPostRedisplay();
}
//End - Glut Function Wrappers

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, ((char **)argv));

	Window MainWindow;
	MainWindow.Init("MSc Assignment : Mini Golf Game");

	Lighting MainLighting;
	MainLighting.InitLights();

	glutDisplayFunc(RenderScene);
	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(RenderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyboardUpFunc);
	glutSpecialFunc(SpecKeyboardFunc);
	glutSpecialUpFunc(SpecKeyboardUpFunc);

	glutMainLoop();
}