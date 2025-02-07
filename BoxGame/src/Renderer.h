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

		const Texture2D& GetWoodTexture() const { return m_Texture; }
		const Texture2D& GetCheckerBoardTexture() const { return m_Texture2; }
		const Texture2D& GetBricketWallTexture() const { return m_Texture3; }

		void RenderIceBlock(const Vector3& position, float width, float height, float length, const Color& color = SKYBLUE) const;

		void RenderTextureCube(const Texture2D& texture, const Vector3& position, float width, float height, float length, const Color& color) const;
		void RenderCube(const Vector3& position, float width, float height, float length, const Color& color) const;
		void RenderTextureRec(const Texture2D& testure, const Rectangle& source, const Vector3& position, float width, float height, float length, const Color& color) const;
		void RenderText(const std::string& text, uint32_t xPos, uint32_t yPos, uint32_t fontSize, const Color& color) const;
		void RenderRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const Color& color) const;
		void RenderRay(const Vector3& position, const Vector3& direction, const Color& color) const;
		void RenderLine(const Vector3& startPos, const Vector3& endPos, const Color& color) const;
		
	private:
		Texture2D m_Texture;
		Texture2D m_Texture2;
		Texture2D m_Texture3;
	};

}