#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>

namespace D3DEngine
{
	class Transform
	{
	public:
		Transform(glm::vec3& Pos = glm::vec3(),
				  glm::vec3& Rot = glm::vec3(),
				  glm::vec3& Scale = glm::vec3(1.0f,1.0f,1.0f)) : 
			m_Pos(Pos), m_Rot(Rot), m_Scale(Scale)
		{
		}
		~Transform(){}

		inline glm::mat4 GetModel() const
		{
			glm::mat4 posMatrix = glm::translate(m_Pos);
			glm::mat4 rotXMatrix = glm::rotate(m_Rot.x, glm::vec3(1,0,0));
			glm::mat4 rotYMatrix = glm::rotate(m_Rot.y, glm::vec3(0,1,0));
			glm::mat4 rotZMatrix = glm::rotate(m_Rot.z, glm::vec3(0,0,1));
			glm::mat4 scaleMatrix = glm::translate(m_Scale);

			glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

			return posMatrix * rotMatrix * scaleMatrix;
		}

		//Getters
		inline glm::vec3& GetPos() { return m_Pos; }
		inline glm::vec3& GetRot() { return m_Rot; }
		inline glm::vec3& GetScale() { return m_Scale; }
		//End - Getters
		//Setters
		inline void SetPos(glm::vec3& Pos) { m_Pos = Pos; }
		inline void SetRot(glm::vec3& Rot) { m_Rot = Rot; }
		inline void SetScale(glm::vec3& Scale) { m_Scale = Scale; }
		//End - Setters
	private:

		glm::vec3 m_Pos;
		glm::vec3 m_Rot;
		glm::vec3 m_Scale;
	};
}