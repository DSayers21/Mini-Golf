#include "Transform.h"

namespace D3DEngine
{
	Transform::Transform()
	{
		m_Translation = Vector3f(0, 0, 0);
	}

	Transform::~Transform()
	{
	}

	Matrix4f Transform::GetTransformation()
	{
		Matrix4f Translation;
		Translation = Translation.InitTranslation(m_Translation.GetX(), m_Translation.GetY(), m_Translation.GetZ());
		return Translation;
	}
}