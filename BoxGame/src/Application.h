#pragma once
#include <memory>

#include "raylib.h"

#include "src/Renderer.h"
#include "src/Window.h"
#include "src/Game.h"
#include "src/Camera.h"

namespace BoxGame {

	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	public:
		static const Application& Get();
		static const Window& GetWindow();
		static const Renderer& GetRenderer();

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
