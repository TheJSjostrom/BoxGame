#include <iostream>

#include "raylib.h"

#include "src/Window.h"
#include "src/Application.h"

namespace BoxGame {

	Window::Window()
	{
		Init();
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init()
	{
		InitWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str());
		SetTargetFPS(60);

		if (!IsWindowReady())
		{
			std::cout << "Window couldn't initialize successfully" << std::endl;
		}
	}

	void Window::Shutdown()
	{
		CloseWindow();
	}

	bool Window::IsWindowClosed()
	{
		return WindowShouldClose();
	}

	void Window::OnUpdate()
	{
	}

}
 