#pragma once

#include <GL/glew.h>
#include <string>
namespace D3DEngine
{
	class RenderUtil
	{
	public:
		static void ClearScreen();
		static void InitGraphics();
		static void SetTextures(bool Enabled);
		static void UnBindTextures();
	};
}