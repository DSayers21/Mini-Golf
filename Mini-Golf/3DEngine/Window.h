#pragma once


#include <tchar.h>
#include <string>
#include <glut.h>

class Window
{
public:
	Window();
	~Window();

	void Init(std::string Title);
};

