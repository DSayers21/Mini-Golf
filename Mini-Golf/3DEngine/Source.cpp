//// Pool Game.cpp : Defines the entry point for the console application.
//#include "vecmath.h"
//#include "Window.h"
//#include "Lighting.h"
//#include "Camera.h"
//
//#include <glut.h>
//#include <math.h>
//#include <tchar.h>
//
//#define SIM_UPDATE_MS (20)
//
//Camera TestCamera;
//
//void RenderScene(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glVertex3f(1.0, 0.0, 0.0);
//	glutSolidTeapot(.5);
//
//	//set camera
//	TestCamera.LookAt();
//
//	glFlush();
//	glutSwapBuffers();
//}
//
//void SpecKeyboardFunc(int key, int x, int y)
//{
//	switch (key)
//	{
//
//	}
//}
//
//void SpecKeyboardUpFunc(int key, int x, int y)
//{
//	switch (key)
//	{
//
//	}
//}
//
//void KeyboardFunc(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case(32):
//	{
//		TestCamera.SetCamRot(false);
//		break;
//	}
//	case('z'):
//	{
//		TestCamera.SetCamL(true);
//		break;
//	}
//	case('c'):
//	{
//		TestCamera.SetCamR(true);
//		break;
//	}
//	case('s'):
//	{
//		TestCamera.SetCamU(true);
//		break;
//	}
//	case('x'):
//	{
//		TestCamera.SetCamD(true);
//		break;
//	}
//	case('f'):
//	{
//		TestCamera.SetCamZin(true);
//		break;
//	}
//	case('v'):
//	{
//		TestCamera.SetCamZout(true);
//		break;
//	}
//	}
//
//}
//
//void KeyboardUpFunc(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case(32):
//	{
//		TestCamera.SetCamRot(false);
//		break;
//	}
//	case('z'):
//	{
//		TestCamera.SetCamL(false);
//		break;
//	}
//	case('c'):
//	{
//		TestCamera.SetCamR(false);
//		break;
//	}
//	case('s'):
//	{
//		TestCamera.SetCamU(false);
//		break;
//	}
//	case('x'):
//	{
//		TestCamera.SetCamD(false);
//		break;
//	}
//	case('f'):
//	{
//		TestCamera.SetCamZin(false);
//		break;
//	}
//	case('v'):
//	{
//		TestCamera.SetCamZout(false);
//		break;
//	}
//	}
//}
//
//void ChangeSize(int w, int h)
//{
//
//	// Prevent a divide by zero, when window is too short
//	// (you cant make a window of zero width).
//	if (h == 0) h = 1;
//	float ratio = 1.0* w / h;
//
//	// Reset the coordinate system before modifying
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	// Set the viewport to be the entire window
//	glViewport(0, 0, w, h);
//
//	// Set the correct perspective.
//	gluPerspective(45, ratio, 0.2, 1000);
//	glMatrixMode(GL_MODELVIEW);
//
//	TestCamera.LookAt();
//}
//
//void UpdateScene(int ms)
//{
//
//
//	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
//	glutPostRedisplay();
//}
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	glutInit(&argc, ((char **)argv));
//
//	Window MainWindow;
//	MainWindow.Init("MSc Workshop : Pool Game");
//
//	Lighting MainLighting;
//	MainLighting.InitLights();
//
//	glutDisplayFunc(RenderScene);
//	glutTimerFunc(SIM_UPDATE_MS, UpdateScene, SIM_UPDATE_MS);
//	glutReshapeFunc(ChangeSize);
//	glutIdleFunc(RenderScene);
//
//	glutIgnoreKeyRepeat(1);
//	glutKeyboardFunc(KeyboardFunc);
//	glutKeyboardUpFunc(KeyboardUpFunc);
//	glutSpecialFunc(SpecKeyboardFunc);
//	glutSpecialUpFunc(SpecKeyboardUpFunc);
//
//	glutMainLoop();
//
//	//return 0;
//}
