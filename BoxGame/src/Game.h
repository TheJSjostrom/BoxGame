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

		bool m_CameraMode = true;
		int m_Timer = 0;
	};

}
