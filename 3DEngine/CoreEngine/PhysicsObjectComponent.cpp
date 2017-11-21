#include "PhysicsObjectComponent.h"

namespace D3DEngine
{
	PhysicsObjectComponent::PhysicsObjectComponent(PhysicsObject* object, bool Control) :
		m_PhysicsObject(object), m_Control(Control)
	{
	}

	PhysicsObjectComponent::~PhysicsObjectComponent()
	{
	}

	void PhysicsObjectComponent::Input(GetInput * input, float Delta)
	{
		if (m_Control)
		{
			if (input->GetKeyDown(KEY_UP))
				m_PhysicsObject->ApplyImpulse(Vector3f(-1.0f, 0, 0));
			if (input->GetKeyDown(KEY_DOWN))
				m_PhysicsObject->ApplyImpulse(Vector3f(1.0f, 0, 0));
			if (input->GetKeyDown(KEY_LEFT))
				m_PhysicsObject->ApplyImpulse(Vector3f(0, 0, -1.0f));
			if (input->GetKeyDown(KEY_RIGHT))
				m_PhysicsObject->ApplyImpulse(Vector3f(0, 0, 1.0f));
			//Release Key
			if (input->GetKeyUp(KEY_UP))
				m_PhysicsObject->ApplyImpulse(Vector3f(0, 0, 0));
			if (input->GetKeyUp(KEY_DOWN))
				m_PhysicsObject->ApplyImpulse(Vector3f(0, 0, 0));
			if (input->GetKeyUp(KEY_LEFT))
				m_PhysicsObject->ApplyImpulse(Vector3f(0, 0, 0));
			if (input->GetKeyUp(KEY_RIGHT))
				m_PhysicsObject->ApplyImpulse(Vector3f(0, 0, 0));
		}
	}

	void PhysicsObjectComponent::Update(float Delta)
	{
		//Set Position
		//std::cerr << m_PhysicsObject->GetPosition().GetX() << " " << m_PhysicsObject->GetPosition().GetY() << " " << m_PhysicsObject->GetPosition().GetZ() << std::endl;
		Transform* Test = GetTransform();
		GetTransform()->SetPosition(m_PhysicsObject->GetPosition());
	}
}