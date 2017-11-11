#pragma once

#include "Transform.h"
#include "Shader.h"

namespace D3DEngine
{
	class GameComponent
	{
	public:
		GameComponent();
		~GameComponent();

		virtual void Input(Transform transform, float Delta);
		virtual void Update(Transform transform, float Delta);
		virtual void Draw(Transform* transform, Shader* shader);
	};
}