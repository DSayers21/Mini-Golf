#pragma once

#include "Transform.h"
#include "GameObject.h"

namespace D3DEngine
{
	class RenderEngine;
	class Shader;

	class GameComponent
	{
	public:
		GameComponent();
		virtual ~GameComponent();

		virtual void Input(GetInput* input, float Delta);
		virtual void Update(float Delta);
		virtual void Draw(Shader* shader, RenderEngine* renderEngine);
		virtual void AddToEngine(MainComp * mainComp);

		virtual inline void SetParent(GameObject* parent) { m_Parent = parent; }
		virtual inline Transform* GetTransform() { return m_Parent->GetTransform(); }

	protected:
		GameObject* m_Parent;
	};
}