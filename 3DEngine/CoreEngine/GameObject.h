#pragma once

#include <vector>
#include "GameObject.h"
#include "GameComponent.h"
#include "Transform.h"

namespace D3DEngine
{
	class RenderEngine;
	class Shader;


	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		GameObject* AddChild(GameObject* Child);
		GameObject* AddComponent(GameComponent* Component);

		void Input(float Delta);
		void Update(float Delta);
		void Draw(Shader* shader);

		//Getters
		inline Transform* GetTransform() { return m_Transform; }

		void AddToRenderingEngine(RenderEngine* renderEngine);

	private:
		std::vector<GameObject*> m_Children = std::vector<GameObject*>();
		std::vector<GameComponent*> m_Components = std::vector<GameComponent*>();
		Transform* m_Transform;
	};
}