#include "GameObject.h"

namespace D3DEngine
{
	GameObject::GameObject(Camera* camera)
	{
		m_Transform = new Transform();
		m_Transform->SetCamera(camera);

		m_Transform->SetProjection(70.0f, 800, 600, 0.1f, 1000.0f);
		m_Transform->SetTranslation(0, -1, 5);
		//m_Transform.SetRotation(0, TempAmount * 180, 0);
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

	void GameObject::Input()
	{
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Input(*m_Transform);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Input();
	}

	void GameObject::Update()
	{
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Update(*m_Transform);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Update();
	}

	void GameObject::Draw(Shader* shader)
	{
		for (int i = 0; i < m_Components.size(); i++)
			m_Components[i]->Draw(m_Transform, shader);

		for (int i = 0; i < m_Children.size(); i++)
			m_Children[i]->Draw(shader);
	}
}