#pragma once
#include "src/Player.h"
#include "raylib.h"

namespace BoxGame {

	class Level
	{
	public:
		Level();

		void OnUpdate(float ts);
		void OnRender();

	private:
		Player m_Player;

		float m_Angle = 0.0f;
		Vector3 m_Vec = { 0.0f, 0.0f, 0.0f };
		Vector3 m_LeftDirection = { 0.0f, 0.0f, 0.0f };

		Vector3 m_CubePosition = { 0.0f, 1.0f, -2.0f };
	};

}