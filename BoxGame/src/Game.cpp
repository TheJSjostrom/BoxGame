#include <iostream>
#include <math.h>
#include <string>

#include "src/Game.h"
#include "src/Application.h"

#include "raymath.h"
#include "raylib.h"

namespace BoxGame {

	Game::Game()
	{ 
		DisableCursor();
	}

	void Game::OnUpdate(float ts)
	{
		if (!nullptr)
		{
			m_Camera.OnUpdate(ts);
			m_Level.OnUpdate(ts);
		}
 
	}

	void Game::OnRender()
	{
		BeginMode3D(m_Camera.GetCamera());
		m_Level.OnRender();
		EndMode3D();
	}

	void Game::OnRenderUI()
	{
		const Renderer& renderer = Application::GetRenderer();
		const Window& window = Application::GetWindow();
		const Vector3& vector = m_Level.GetVector();
		const Vector3& vector2 = m_Level.GetLeftVector();

		// Render Game Title
		s += 0.0166666667f;
		m_Timer++;
		if (m_Timer % 120 < 60)
			GameTitle(renderer, window);

		renderer.RenderRectangle(3, 90, 150, 200, { 10, 10, 10, 200 });

		const std::string xValue = std::to_string(vector.x);
		const std::string yValue = std::to_string(vector.y);
		renderer.RenderText("y: " + yValue, 10, 130, 22, DARKBLUE);
		renderer.RenderText("x: " + xValue, 10, 100, 22, RED);

		const std::string xValue2 = std::to_string(vector2.x);
		const std::string yValue2 = std::to_string(vector2.y);
		renderer.RenderText("y: " + yValue2, 10, 190, 22, DARKBLUE);
		renderer.RenderText("x: " + xValue2, 10, 170, 22, RED);
	}

	void Game::GameTitle(const Renderer& renderer, const Window& window) const
	{
		renderer.RenderRectangle(480, 0, 340, 80, { 10, 10, 10, 220 });
		renderer.RenderText(window.GetName(), 500 + 7, 5 + 7, 70, BLACK);
		renderer.RenderText(window.GetName(), 500, 5, 70, GRAY);
	}
}