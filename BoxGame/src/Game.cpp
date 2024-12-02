#include "Game.h"
#include <math.h>
#include <iostream>
#include "raymath.h"
#include "raylib.h"
#include "Application.h"

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
        BeginMode3D(m_Camera.GetCamera());
        m_Level.OnRender();
        EndMode3D();
	}

}