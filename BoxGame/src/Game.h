#pragma once
#include <array>

#include "src/Camera.h"
#include "src/Mesh.h"
#include "src/Level.h"
#include "src/Renderer.h"
#include "src/Window.h"

namespace BoxGame {

	class Game
	{
	public:
		Game();

		void OnUpdate(const float ts);

		void OnRender();
		void OnUIRender();

	private:
		void GameTitle(const Renderer& renderer, const Window& window) const;

	private:
		Camera m_Camera;
		Level m_Level;

		Rectangle rec = { 480, 0, 340, 80 };
		Rectangle rec2 = { 140, 10, 34, 34};

		Ray m_Ray = { 0.0f };
		RayCollision m_Collision = { 0.0f };

		bool m_Play = false;
		bool m_CameraMode = true;
		uint32_t m_Timer = 0;
	};

}
