#include "GameObject.h"
#include "RenderEngine.h"
#include "Shader.h"
#include "GameComponent.h"
#include <iostream>
namespace D3DEngine
{
	GameObject::GameObject()
	{
		m_Transform = new Transform();
	}

	GameObject::~GameObject()
	{

	}

	GameObject* GameObject::AddChild(GameObject* Child)
	{
		m_Children.push_back(Child);
		Child->GetTransform()->SetParent(m_Transform);
		return this;
	}

	GameObject* GameObject::AddComponent(GameComponent* Component)
	{
		Component->SetParent(this);
		m_Components.push_back(Component);
		return this;
	}

	void GameObject::Input(GetInput* input, float Delta)
	{
		m_Transform->Update();
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Input(input, Delta);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Input(input, Delta);
	}

	void GameObject::Update(float Delta)
	{
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Update(Delta);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Update(Delta);
	}

	void GameObject::Draw(Shader* shader, RenderEngine* renderEngine)
	{
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Draw(shader, renderEngine);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Draw(shader, renderEngine);
	}

	void GameObject::AddToRenderingEngine(RenderEngine * renderEngine)
	{
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->AddToRenderingEngine(renderEngine);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->AddToRenderingEngine(renderEngine);
	}
}