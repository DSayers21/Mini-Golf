#pragma once

//Includes
#include <iostream>
#include <vector>
#include "Transform.h"
#include "Input.h"

namespace D3DEngine
{
	//Forward Declarations
	class RenderEngine;
	class Shader;
	class GameComponent;
	class MainComp;

	class GameObject
	{
	public:
		//Constructor
		GameObject();
		//Destructor
		~GameObject();
		//Clear all objects from the tree
		void ClearGameObject();
		//Destroy the object
		void Destroy();
		//Add child object to the object
		GameObject* AddChild(GameObject* Child);
		//Add component to the object
		GameObject* AddComponent(GameComponent* Component);

		//Input, Update and Draw handeling functions
		void Input(GetInput* input, float Delta);
		void Update(float Delta);
		void Draw(Shader* shader, RenderEngine* renderEngine);

		//Getters
		inline Transform* GetTransform() { return m_Transform; }
		std::vector<GameObject*> GetAllAttached();

		//Setters
		//Add the main comp to all objects attached
		void SetEngine(MainComp * mainComp);
		inline void SetVisible(bool Visible) { m_Visible = Visible; }
		inline void SetActive(bool Active) { m_Active = Active; }
	private:
		//List of children objects
		std::vector<GameObject*> m_Children = std::vector<GameObject*>();
		//List of components attached to the object
		std::vector<GameComponent*> m_Components = std::vector<GameComponent*>();
		//Transform of the object
		Transform* m_Transform;
		//Pointer to the main component
		MainComp* m_MainComp;
		//Visibility status
		bool m_Visible = true;
		//Active Status
		bool m_Active = true;
	};
}