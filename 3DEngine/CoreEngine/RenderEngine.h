#pragma once

#include "GameObject.h"
#include "BasicShader.h"

namespace D3DEngine
{
	class RenderEngine
	{
	public:
		RenderEngine();
		~RenderEngine();

		void Render(GameObject* Object);
	private:
		BasicShader* BShade;
	};
}