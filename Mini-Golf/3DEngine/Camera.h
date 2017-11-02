#pragma once

#include <glut.h>
#include "Vecmath.h"

namespace D3DEngine
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Reset();

		void DoCamera(int ms);
		void LookAt();

		//Setters
		void SetCamPos(vec3 CamPos) { m_gCamPos = CamPos; }
		void SetCamLookAt(vec3 CamLookAt) { m_gCamLookAt = CamLookAt; }
		//----
		void SetCamRot(bool CamRot) { m_gCamRotate = CamRot; }
		void SetCamL(bool CamL) { m_gCamL = CamL; }
		void SetCamR(bool CamR) { m_gCamR = CamR; }
		void SetCamU(bool CamU) { m_gCamU = CamU; }
		void SetCamD(bool CamD) { m_gCamD = CamD; }
		void SetCamZin(bool CamZin) { m_gCamZin = CamZin; }
		void SetCamZout(bool CamZout) { m_gCamZout = CamZout; }
		//Getters
		vec3 GetCamPos() { return m_gCamPos; }
		vec3 GetCamLookAt() { return m_gCamLookAt; }

	private:
		vec3 m_gCamPos;
		vec3 m_gCamLookAt;

		float m_gCamRotSpeed;
		float m_gCamMoveSpeed;

		//Camera Move
		bool m_gCamRotate;
		bool m_gCamL;
		bool m_gCamR;
		bool m_gCamU;
		bool m_gCamD;
		bool m_gCamZin;
		bool m_gCamZout;
	};
}