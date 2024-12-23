#pragma once
#include <string>

#include "raylib.h"

namespace BoxGame {

	class Renderer
	{
	public:
		Renderer();
		
		void Init();

		const Texture2D& GetTexture() const { return m_Texture; }

		void RenderCube(const Rectangle& source, const Vector3& position, float width, float height, float length, const Color& color) const;
		void RenderText(const std::string& text, int xPos, int yPos, int fontSize, const Color& color) const;

	private:
		Texture2D m_Texture;
	};

}