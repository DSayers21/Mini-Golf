#pragma once

#include "Transform.h"

namespace D3DEngine
{
	class RenderEngine;
	class Shader;

	class GameComponent
	{
	public:
		GameComponent();
		~GameComponent();

		virtual void Input(Transform transform, float Delta);
		virtual void Update(Transform transform, float Delta);
		virtual void Draw(Transform* transform, Shader* shader);

		virtual void AddToRenderingEngine(RenderEngine* renderEngine);
	};
}