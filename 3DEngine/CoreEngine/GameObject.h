#pragma once

#include <vector>
#include "GameObject.h"
#include "GameComponent.h"
#include "Transform.h"
#include "Shader.h"

namespace D3DEngine
{
	class GameObject
	{
	public:
		GameObject(Camera* camera);
		~GameObject();

		GameObject* AddChild(GameObject* Child);
		GameObject* AddComponent(GameComponent* Component);

		void Input();
		void Update();
		void Draw(Shader* shader);

		//Getters
		inline Transform* GetTransform() { return m_Transform; }

	private:
		std::vector<GameObject*> m_Children = std::vector<GameObject*>();
		std::vector<GameComponent*> m_Components = std::vector<GameComponent*>();
		Transform* m_Transform;
	};
}