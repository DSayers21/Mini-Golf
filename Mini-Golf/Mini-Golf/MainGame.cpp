#include "MainGame.h"



MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}


void MainGame::RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw Events
	glColor3f(1.0, 0.0, 0.0);
	glutSolidTeapot(.5);

	//set camera
	TestCamera.LookAt();

	glFlush();
	glutSwapBuffers();
}

void MainGame::SpecKeyboardFunc(int key, int x, int y)
{
	switch (key)
	{

	}
}

void MainGame::SpecKeyboardUpFunc(int key, int x, int y)
{
	switch (key)
	{

	}
}

void MainGame::KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case(32):
	{
		TestCamera.SetCamRot(false);
		break;
	}
	case('z'):
	{
		TestCamera.SetCamL(true);
		break;
	}
	case('c'):
	{
		TestCamera.SetCamR(true);
		break;
	}
	case('s'):
	{
		TestCamera.SetCamU(true);
		break;
	}
	case('x'):
	{
		TestCamera.SetCamD(true);
		break;
	}
	case('f'):
	{
		TestCamera.SetCamZin(true);
		break;
	}
	case('v'):
	{
		TestCamera.SetCamZout(true);
		break;
	}
	}

}

void MainGame::KeyboardUpFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case(32):
	{
		TestCamera.SetCamRot(true);
		break;
	}
	case('z'):
	{
		TestCamera.SetCamL(false);
		break;
	}
	case('c'):
	{
		TestCamera.SetCamR(false);
		break;
	}
	case('s'):
	{
		TestCamera.SetCamU(false);
		break;
	}
	case('x'):
	{
		TestCamera.SetCamD(false);
		break;
	}
	case('f'):
	{
		TestCamera.SetCamZin(false);
		break;
	}
	case('v'):
	{
		TestCamera.SetCamZout(false);
		break;
	}
	}
}

void MainGame::ChangeSize(int w, int h)
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

	TestCamera.LookAt();
}

void MainGame::UpdateScene(int ms)
{
	//Do Updates

	//End - Do Updates
	TestCamera.DoCamera(ms);
}