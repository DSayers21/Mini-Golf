#include "Camera.h"

namespace D3DEngine
{
	Camera::Camera()
	{
		Reset();
	}


	Camera::~Camera()
	{
	}

	void Camera::Reset()
	{
		//Sets all Values to the default
		m_gCamPos = vec3(0.0, 0.7, 2.1);
		m_gCamLookAt = vec3(0.0, 0.0, 0.0);

		m_gCamRotate = true;

		m_gCamRotSpeed = 0.2;
		m_gCamMoveSpeed = 0.5;

		//Camera Move
		m_gCamL = false;
		m_gCamR = false;
		m_gCamU = false;
		m_gCamD = false;
		m_gCamZin = false;
		m_gCamZout = false;
	}

	void Camera::DoCamera(int ms)
	{
		static const vec3 up(0.0, 1.0, 0.0);

		if (m_gCamRotate)
		{
			if (m_gCamL)
			{
				vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
				vec3 localL = up.Cross(camDir);
				vec3 inc = (localL* ((m_gCamRotSpeed*ms) / 1000.0));
				m_gCamLookAt = m_gCamPos + camDir + inc;
			}
			if (m_gCamR)
			{
				vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
				vec3 localR = up.Cross(camDir);
				vec3 inc = (localR* ((m_gCamRotSpeed*ms) / 1000.0));
				m_gCamLookAt = m_gCamPos + camDir - inc;
			}
			if (m_gCamU)
			{
				vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
				vec3 localR = camDir.Cross(up);
				vec3 localUp = localR.Cross(camDir);
				vec3 inc = (localUp* ((m_gCamMoveSpeed*ms) / 1000.0));
				m_gCamLookAt = m_gCamPos + camDir + inc;
			}
			if (m_gCamD)
			{
				vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
				vec3 localR = camDir.Cross(up);
				vec3 localUp = localR.Cross(camDir);
				vec3 inc = (localUp* ((m_gCamMoveSpeed*ms) / 1000.0));
				m_gCamLookAt = m_gCamPos + camDir - inc;
			}
		}
		else
		{
			if (m_gCamL)
			{
				vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
				vec3 localL = up.Cross(camDir);
				vec3 inc = (localL* ((m_gCamMoveSpeed*ms) / 1000.0));
				m_gCamPos += inc;
				m_gCamLookAt += inc;
			}
			if (m_gCamR)
			{
				vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
				vec3 localR = camDir.Cross(up);
				vec3 inc = (localR* ((m_gCamMoveSpeed*ms) / 1000.0));
				m_gCamPos += inc;
				m_gCamLookAt += inc;
			}
			if (m_gCamU)
			{
				vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
				vec3 localR = camDir.Cross(up);
				vec3 localUp = localR.Cross(camDir);
				vec3 inc = (localUp* ((m_gCamMoveSpeed*ms) / 10000.0));
				m_gCamPos += inc;
				m_gCamLookAt += inc;
			}
			if (m_gCamD)
			{
				vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
				vec3 localR = camDir.Cross(up);
				vec3 localDown = camDir.Cross(localR);
				vec3 inc = (localDown* ((m_gCamMoveSpeed*ms) / 10000.0));
				m_gCamPos += inc;
				m_gCamLookAt += inc;
			}
		}

		if (m_gCamZin)
		{
			vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
			vec3 inc = (camDir* ((m_gCamMoveSpeed*ms) / 1000.0));
			m_gCamPos += inc;
			m_gCamLookAt += inc;
		}
		if (m_gCamZout)
		{
			vec3 camDir = (m_gCamLookAt - m_gCamPos).Normalised();
			vec3 inc = (camDir* ((m_gCamMoveSpeed*ms) / 1000.0));
			m_gCamPos -= inc;
			m_gCamLookAt -= inc;
		}
	}

	void Camera::LookAt()
	{
		glLoadIdentity();
		gluLookAt(m_gCamPos(0), m_gCamPos(1), m_gCamPos(2), m_gCamLookAt(0), m_gCamLookAt(1), m_gCamLookAt(2), 0.0f, 1.0f, 0.0f);
	}
}