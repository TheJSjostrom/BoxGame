#pragma once
#include "raylib.h"

namespace BoxGame {

	class Player
	{
	public:
		Player() = default;

		void Init();

		void OnUpdate(float ts);
		void OnRender();

	private:
		Vector3 m_ModelTarget = { 0.0f, 0.0f, 0.0f };
		Vector3 m_FrontDirection = { 0.0f, 0.0f, -1.0f };
		Vector3 m_Position = { 0.0f, 0.0f, 0.0f };

		Model m_Model;

		float ModelRotationAngle = 90.0f;
		float m_FrontDirectionAngle = 0.0f;
	};

}
 