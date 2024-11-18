#include <iostream>
#include "src/Application.h"
#include "raylib.h"

namespace BoxGame {

	Application::Application() 
	{
		m_Game = std::make_unique<Game>();
		DisableCursor();
	
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// Application loop
		while (m_Running)
		{
			float time = (float)GetTime();
			float timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (m_Window.IsWindowClosed())
				m_Running = false;
			
			OnUpdate(timestep);
			OnRender();
			m_Window.OnUpdate();
		}
	}

	void Application::OnUpdate(float ts)
	{
		m_Game->OnUpdate(ts);
	}

	void Application::OnRender()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawFPS(0, 0);
		m_Game->OnRender();
		EndDrawing();
	}

}