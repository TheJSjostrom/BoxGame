#include "raylib.h"

#include "src/Application.h"

namespace BoxGame {

	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		s_Instance = this;
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
			const float time = (float)GetTime();
			const float timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (m_Window.IsWindowClosed())
				m_Running = false;
			
			OnUpdate(timestep);
			OnRender();
			//m_Window.OnUpdate();
		}
		 
	}

	void Application::OnUpdate(const float ts)
	{
		m_Game.OnUpdate(ts);
	}

	void Application::OnRender()
	{
		ClearBackground({ 32,32,32,255});

		BeginDrawing();
		m_Game.OnRender();
		m_Game.OnUIRender();
		DrawFPS(10, 10);
		EndDrawing();	 
	}

}