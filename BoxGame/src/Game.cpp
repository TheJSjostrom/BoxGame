#include <iostream>
#include <math.h>

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
		m_Camera.OnUpdate(ts);
        m_Level.OnUpdate(ts);
	}

	void Game::OnRender()
	{
		Renderer& renderer = Application::Get().GetRenderer();
		Window& window = Application::Get().GetWindow();
		renderer.RenderText(window.GetName(), 500, 0, 50, GRAY);
		
        BeginMode3D(m_Camera.GetCamera());
        m_Level.OnRender();
        EndMode3D();
	}

}