#pragma once
#include <memory>

#include "src/Renderer.h"
#include "src/Window.h"
#include "src/Game.h"
#include "src/Camera.h"

#include "raylib.h"
 
namespace BoxGame {

	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	public:
		static Application& Get();
		static Window& GetWindow();
		static Renderer& GetRenderer();

	private:
		void OnUpdate(float ts);
		void OnRender();

	private:
		Window m_Window;
		Renderer m_Renderer;
		std::unique_ptr<Game> m_Game;

		bool m_Running = true;
		float m_LastFrameTime = 0.0f;
	};

}
