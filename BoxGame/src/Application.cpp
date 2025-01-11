#include <iostream>
#include <string>

#include "raylib.h"

#include "src/Application.h"

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

	const Application& Application::Get()
	{
		return *s_Instance;
	}

	const Window& Application::GetWindow()
	{
		return Get().m_Window;
	}

	const Renderer& Application::GetRenderer()
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
		ClearBackground(BLACK);

		BeginDrawing();
		m_Game->OnRender();
		m_Game->OnUIRender();
		DrawFPS(10, 10);
		EndDrawing();	 
	}

}