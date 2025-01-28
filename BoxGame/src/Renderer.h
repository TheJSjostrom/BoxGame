#pragma once
#include <string>

#include "raylib.h"

namespace BoxGame {

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Init();
		void Shutdown();

		const Texture2D& GetTexture() const { return m_Texture; }

		void RenderIceBlock(const Vector3& position, float width, float height, float length, const Color& color = SKYBLUE) const;

		void RenderCube(const Vector3& position, float width, float height, float length, const Color& color) const;
		void RenderTextureCube(const Rectangle& source, const Vector3& position, float width, float height, float length, const Color& color) const;
		void RenderText(const std::string& text, int xPos, int yPos, int fontSize, const Color& color) const;
		void RenderRectangle(int x, int y, int width, int height, const Color& color) const;
		void RenderRay(const Vector3& position, const Vector3& direction, const Color& color) const;
		void RenderLine(const Vector3& startPos, const Vector3& endPos, const Color& color) const;
		
	private:
		Texture2D m_Texture;
	};

}