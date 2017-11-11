#pragma once

#include "GameObject.h"
#include "BasicShader.h"
#include "Camera.h"

namespace D3DEngine
{
	class RenderEngine
	{
	public:
		RenderEngine();
		~RenderEngine();

		void Render(GameObject* Object);

		inline void SetCamera(Camera* camera) { m_Camera = camera; }
		inline Camera* GetCamera() { return m_Camera; }

	private:
		BasicShader* BShade;
		Camera* m_Camera;
	};
}