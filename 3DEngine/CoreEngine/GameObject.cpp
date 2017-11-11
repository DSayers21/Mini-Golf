#include "GameObject.h"

namespace D3DEngine
{
	GameObject::GameObject()
	{
		m_Transform = new Transform();

		m_Transform->SetPosition(0, -1, 5);
		m_Transform->SetScaling(.4, .4, .4);
	}

	GameObject::~GameObject()
	{

	}

	GameObject* GameObject::AddChild(GameObject* Child)
	{
		m_Children.push_back(Child);
		return this;
	}

	GameObject* GameObject::AddComponent(GameComponent* Component)
	{
		m_Components.push_back(Component);
		return this;
	}

	void GameObject::Input(float Delta)
	{
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Input(*m_Transform, Delta);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Input(Delta);
	}

	void GameObject::Update(float Delta)
	{
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Update(*m_Transform, Delta);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Update(Delta);
	}

	void GameObject::Draw(Shader* shader)
	{
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Draw(m_Transform, shader);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Draw(shader);
	}
}