#pragma once
#include <string>

#include "raylib.h"

namespace BoxGame {

	class Renderer
	{
	public:
		Renderer() = default;

		void RenderText(const std::string& text, int xPos, int yPos, int fontSize, const Color& color);

	};

}