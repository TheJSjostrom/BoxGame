#pragma once
#include "Camera.h"
#include "Player.h"

namespace BoxGame {

	class Game
	{
	public:
		Game();

		void OnUpdate(float ts);
		void OnRender();

	private:
		bool m_FirstRender = true;
		float m_Yaw = 0.0f;
		float m_Pitch = 0.0f;
		float m_Angle = 3.1314f;
		float m_LastMouseX = 640.0f;
		float m_LastMouseY = 0.0f;
		float m_Fov = 45.0f;
		float m_CameraSpeed = 5.0f;

		
		Vector3 m_FrontDirection;
		Vector3 m_Target = { 0.0f, 0.0f, 0.0f };
		Vector3 m_Position = { 0.0f, 0.5f, 0.0f };
	
		Camera m_Camera;
		Player m_Player;

		Vector3 m_StartTarget;
		Vector3 m_EndTarget;
		Vector3 m_StartPos;
		Vector3 m_EndPos;
		Vector3 m_StartCamDir;
		Vector3 m_EndCamDir;
	};

}
