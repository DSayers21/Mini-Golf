#pragma once

#include <iostream>
#include <vector>
#include "Transform.h"
#include "Input.h"

namespace D3DEngine
{
	class RenderEngine;
	class Shader;
	class GameComponent;
	class MainComp;

	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		GameObject* AddChild(GameObject* Child);
		GameObject* AddComponent(GameComponent* Component);


		void Input(GetInput* input, float Delta);
		void Update(float Delta);
		void Draw(Shader* shader, RenderEngine* renderEngine);

		//Getters
		inline Transform* GetTransform() { return m_Transform; }

		void SetEngine(MainComp * mainComp);

		std::vector<GameObject*> GetAllAttached();

		//Setters
		inline void SetVisible(bool Visible) { m_Visible = Visible; }
		inline void SetActive(bool Active) { m_Active = Active; }
	private:
		std::vector<GameObject*> m_Children = std::vector<GameObject*>();
		std::vector<GameComponent*> m_Components = std::vector<GameComponent*>();
		Transform* m_Transform;
		MainComp* m_MainComp;

		bool m_Visible = true;
		bool m_Active = true;
	};
}