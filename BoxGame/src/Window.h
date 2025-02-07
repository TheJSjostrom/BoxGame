#pragma once
#include <string>

namespace BoxGame {

	struct WindowData
	{
		std::string Title = "BoxGame";
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool VSync = true;
	};

	class Window
	{
	public:
		Window();
		~Window();

		void OnUpdate();
		bool IsWindowClosed();

		uint32_t GetWidth() const { return m_Data.Width; }
		uint32_t GetHeight() const { return m_Data.Height; }

		const std::string& GetName() const { return m_Data.Title; }
		const WindowData& GetWindowData() const { return m_Data; }

	private:
		void Init();
		void Shutdown();

	private:
		WindowData m_Data;
	};

}
 