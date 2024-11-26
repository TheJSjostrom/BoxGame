#pragma once
#include <string>

namespace BoxGame {

	struct WindowData
	{
		std::string Title = "BoxGame";
		unsigned int Width = 1280;
		unsigned int Height = 720;
		bool VSync = true;
	};

	class Window
	{
	public:
		Window();
		~Window();

		void OnUpdate();
		bool IsWindowClosed();

		int GetWidth() const { return m_Data.Width; }
		int GetHeight() const { return m_Data.Height; }
		const WindowData& GetWindowData() const { return m_Data; }
	private:
		void Init();
		void Shutdown();

	private:
		WindowData m_Data;
	};

}
 