#pragma once

#include "src/Window.h"
#include "src/Game.h"
#include <memory>
#include "raylib.h"
#include "Camera.h"

namespace BoxGame {

	class Application
	{
	public:
		Application();
		~Application();

		void Run();
	
		const Window& GetWindow() const { return m_Window; }
	public:
		static Application& Get();
	private:
		void OnUpdate(float ts);
		void OnRender();

	private:
		Window m_Window;
		std::unique_ptr<Game> m_Game;

		bool m_Running = true;
		float m_LastFrameTime = 0.0f;
	};

}
