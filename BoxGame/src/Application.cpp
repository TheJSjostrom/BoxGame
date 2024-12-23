#include <iostream>
#include <string>

#include "src/Application.h"

#include "raylib.h"
 

namespace BoxGame {

	static Application* s_Instance = nullptr;

	Application::Application() 
	{
		s_Instance = this;
		m_Game = std::make_unique<Game>(); 
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	Application& Application::Get()
	{
		return *s_Instance;
	}

	Window& Application::GetWindow()
	{
		return Get().m_Window;
	}

	Renderer& Application::GetRenderer()
	{
		return Get().m_Renderer;
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
		m_Game->OnRender();	 
		DrawFPS(10, 10);
		EndDrawing();
	}

}