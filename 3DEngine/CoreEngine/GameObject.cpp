//Includes
#include "GameObject.h"
#include "RenderEngine.h"
#include "Shader.h"
#include "GameComponent.h"
#include "MainComp.h"

namespace D3DEngine
{
	GameObject::GameObject()
	{
		//Create new transform
		m_Transform = new Transform();
		//Set maincomp to nullptr
		m_MainComp = nullptr;
	}

	GameObject::~GameObject()
	{
		//Display Message
		std::cerr << "Destructor: Game Object" << std::endl;
		//Delete the transform
		delete m_Transform;
	}

	void GameObject::ClearGameObject()
	{
		//Loop over all components, and delete each one
		for (int i = 0; i < m_Components.size(); i++)
			delete m_Components[i];
		m_Components.clear();	//Clear the list
		//Loop over all children objects, and delete each one
		for (int i = 0; i < m_Children.size(); i++)
		{
			//Clear the children node
			m_Children[i]->ClearGameObject();
			delete m_Children[i];	//Delete the child
		}
		m_Children.clear();		//Clear the list
	}

	void GameObject::Destroy()
	{
		//Empty
	}

	GameObject* GameObject::AddChild(GameObject* Child)
	{
		//Add child to the list
		m_Children.push_back(Child);
		//Set the childs main comp
		Child->SetEngine(m_MainComp);
		//Set the parent of the child
		Child->GetTransform()->SetParent(m_Transform);
		return this;	//Return this object
	}

	GameObject* GameObject::AddComponent(GameComponent* Component)
	{
		//Set the parent of the component to the current object
		Component->SetParent(this);
		//Add to the list
		m_Components.push_back(Component);
		return this;	//Return this objec
	}

	void GameObject::Input(GetInput* input, float Delta)
	{
		//Update the transform
		m_Transform->Update();
		//Loop over all components
		for (int i = 0; i < m_Components.size(); i++)
			if (m_Active)	//Check if component is active
				m_Components[i]->Input(input, Delta);	//Handle input for component
		//Loop over all children, and handle their input
		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Input(input, Delta);
	}

	void GameObject::Update(float Delta)
	{
		//Loop over all components, and update them
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Update(Delta);
		//Loop over all children, and update them
		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Update(Delta);
	}

	void GameObject::Draw(Shader* shader, RenderEngine* renderEngine)
	{
		//Loop over all components
		for (int i = 0; i < m_Components.size(); i++)
			if(m_Visible)	//Check if component is visible
				m_Components[i]->Draw(shader, renderEngine);	//Draw the component
		//Loop over all the children and draw them
		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Draw(shader, renderEngine);
	}

	void GameObject::SetEngine(MainComp* mainComp)
	{
		//Check if engine hasnt been set yet
		if (m_MainComp != mainComp)
		{
			//Set the main component
			m_MainComp = mainComp;
			//Loop over all components, and set the main component
			for (int i = 0; i < m_Components.size(); i++)
				m_Components[i]->AddToEngine(mainComp);
			//Loop over all children, and set the main component
			for (int i = 0; i < m_Children.size(); i++)
				m_Children[i]->SetEngine(mainComp);
		}
	}

	std::vector<GameObject*> GameObject::GetAllAttached()
	{
		//List of objects
		std::vector<GameObject*> Result = std::vector<GameObject*>();
		//Loop over all the children
		for (int i = 0; i < m_Children.size(); i++)
		{
			//Get all the objects attached to the child
			std::vector<GameObject*> ChilResult = m_Children[i]->GetAllAttached();
			//Add all the objects of the child to the list
			Result.insert(std::end(ChilResult), std::begin(ChilResult), std::end(ChilResult));
		}
		//Add the current object to the list
		Result.push_back(this);
		//Return all the objects
		return Result;
	}
}