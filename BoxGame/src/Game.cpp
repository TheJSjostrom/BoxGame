#include <iostream>
 
#include "src/Game.h"
#include "src/Application.h"
#include <raymath.h>
#include "raylib.h"

namespace BoxGame {

	Game::Game()
	{ 
		DisableCursor();
	}

	void Game::OnUpdate(const float ts)
	{
		m_Timer++;
	
		if (IsKeyPressed(KEY_ONE))
		{
			DisableCursor();
			m_CameraMode = true;
		}
		else if (IsKeyPressed(KEY_TWO))
		{
			DisableCursor();
			m_CameraMode = false;
		}

		if (m_CameraMode)
		{
			m_Camera.OnUpdate(ts);
		}

		m_Level.OnUpdate(ts);
	}

	void Game::OnRender()
	{
		BeginMode3D(m_Camera.GetCamera());
		m_Level.OnRender();
		EndMode3D();
	}

	void Game::OnUIRender()
	{
		const Renderer& renderer = Application::GetRenderer();
		const Window& window = Application::GetWindow();

		// Render Game Title
		if (m_Timer % 120 < 60)
		{
			GameTitle(renderer, window);
		}
	}

	void Game::GameTitle(const Renderer& renderer, const Window& window) const
	{
		renderer.RenderRectangle(480, 0, 340, 80, { 10, 10, 10, 220 });
		renderer.RenderText(window.GetName(), 500 + 7, 5 + 7, 70, BLACK);
		renderer.RenderText(window.GetName(), 500, 5, 70, GRAY);
	}

}