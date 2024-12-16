#include "src/Renderer.h"
#include "raylib.h"

namespace BoxGame {

	void Renderer::RenderText(const std::string& text, int xPos, int yPos, int fontSize, const Color& color)
	{
		DrawText(text.c_str(), xPos, yPos, fontSize, color);
	}

}