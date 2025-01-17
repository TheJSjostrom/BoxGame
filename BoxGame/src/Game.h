#pragma once
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

		void OnUpdate(float ts);

		void OnRender();
		void OnUIRender();

	private:
		void GameTitle(const Renderer& renderer, const Window& window) const;

	private:
		Camera m_Camera;
		Level m_Level;

		int m_Timer = 0;
	};

}
