#pragma once

//Includes
#include "Transform.h"
#include "GameObject.h"

namespace D3DEngine
{
	//Forward declarations
	class RenderEngine;
	class Shader;

	class GameComponent
	{
	public:
		//Constructor
		GameComponent();
		//Virtual destructor
		virtual ~GameComponent();

		//Virtual, Input, Update, Draw, AddToEngine functions
		virtual void Input(GetInput* input, float Delta);
		virtual void Update(float Delta);
		virtual void Draw(Shader* shader, RenderEngine* renderEngine);
		virtual void AddToEngine(MainComp * mainComp);

		//Virtual Getters
		virtual inline Transform* GetTransform() { return m_Parent->GetTransform(); }

		//Virtual Setters
		virtual inline void SetParent(GameObject* parent) { m_Parent = parent; }

	protected:
		//Pointer to the parent of the component
		GameObject* m_Parent;
	};
}