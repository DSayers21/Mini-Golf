#pragma once

#include <vector>
#include "GameComponent.h"
#include "Transform.h"

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
		void Draw();

		//Getters
		inline Transform* GetTransform() { return m_Transform; }

	private:
		std::vector<GameObject*> m_Children = std::vector<GameObject*>();
		std::vector<GameComponent*> m_Components = std::vector<GameComponent*>();
		Transform* m_Transform;
	};
}