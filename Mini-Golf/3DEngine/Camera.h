#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace D3DEngine
{
	class Camera
	{
	public:
		Camera(const glm::vec3& Pos, float Fov, float Aspect, float ZNear, float zFar)
		{
			m_Perspective = glm::perspective(Fov, Aspect, ZNear, zFar);
			m_Position = Pos;
			m_Forward = glm::vec3(0, 0, 1);
			m_Up = glm::vec3(0, 1, 0);
		}

		inline glm::mat4 GetViewProjection() const
		{
			//Where you are looking, Where you want to look, Where is up
			return m_Perspective * glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
		}

	private:
		glm::mat4 m_Perspective;
		glm::vec3 m_Position;
		glm::vec3 m_Forward;
		glm::vec3 m_Up;
	};
}