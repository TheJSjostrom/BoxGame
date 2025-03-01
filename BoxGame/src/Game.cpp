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
	
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rec2) && !m_Play)
		{
			//DisableCursor();
			m_Play = true;
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rec2) && m_Play)
		{
			//EnableCursor();
			m_Play = false;
		}

		if (m_Play)
			m_Level.OnUpdate(ts);

		else if (!m_Play)
			m_Camera.OnUpdate(ts);
		
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !m_Play && !CheckCollisionPointRec(GetMousePosition(), rec2))
		{
			m_Ray = GetMouseRay(GetMousePosition(), m_Camera.GetCamera());

			BoundingBox box;
			box.min = { m_Level.GetCubePosition().x - 6.0f / 2, m_Level.GetCubePosition().y - 6.0f / 2, m_Level.GetCubePosition().z - 2.0f / 2};
			box.max = { m_Level.GetCubePosition().x + 6.0f / 2, m_Level.GetCubePosition().y + 6.0f / 2,m_Level.GetCubePosition().z + 2.0f / 2 };

			 m_Collision = GetRayCollisionBox(m_Ray, box);
		}

	}

	void Game::OnRender()
	{
		const Renderer& renderer = Application::GetRenderer();

		BeginMode3D(m_Camera.GetCamera());

		if (m_Collision.hit)
		{
			DrawCubeWires(m_Level.GetCubePosition(), 6.5f, 6.5f, 2.5f, MAROON);
		}

		//renderer.RenderRay(m_Ray.position, m_Ray.direction, RED);
		 
		m_Level.OnRender();
		EndMode3D();
	}

	void Game::OnUIRender()
	{
		const Renderer& renderer = Application::GetRenderer();
		const Window& window = Application::GetWindow();

		renderer.RenderRectangle(rec2.x, rec2.y, rec2.width, rec2.height, { 10, 10, 10, 255 });

		if (!m_Play)
		{
			renderer.RenderTexture(renderer.GetPlayButtonTexture(), rec2.x, rec2.y, WHITE);
		}
		else if (m_Play)
		{
			renderer.RenderTexture(renderer.GetPauseButtonTexture(), rec2.x, rec2.y, WHITE);
		}
 
		// Render Game Title
		if (m_Timer % 120 < 60)
		{
			GameTitle(renderer, window);
		}
	}

	void Game::GameTitle(const Renderer& renderer, const Window& window) const
	{
		renderer.RenderRectangle(rec.x, rec.y, rec.width, rec.height, { 10, 10, 10, 220 });
		renderer.RenderText(window.GetName(), 500 + 7, 5 + 7, 70, BLACK);
		renderer.RenderText(window.GetName(), 500, 5, 70, GRAY);
	}

}