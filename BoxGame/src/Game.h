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
		Camera m_Camera;
		Player m_Player;

		Texture2D m_Texture;
		Vector3 m_StartTarget;
		Vector3 m_EndTarget;
		Vector3 m_StartPos;
		Vector3 m_EndPos;
		Vector3 m_StartCamDir;
		Vector3 m_EndCamDir;
	};

}
