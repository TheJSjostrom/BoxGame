#pragma once
#include "src/Player.h"
#include "raylib.h"

namespace BoxGame {

	class Level
	{
	public:
		Level();

		void OnUpdate(float ts);
		void OnRender();

	private:
		void DrawCubeTextureRec(const Texture2D& texture, const Rectangle& source, const Vector3& position, float width, float height, float length, const Color& color);

	private:
		Player m_Player;

		float m_Angle = 0.0f;
		Vector3 m_Vec = { 0.0f, 0.0f, 0.0f };
		Vector3 m_LeftDirection = { 0.0f, 0.0f, 0.0f };

		Vector3 m_CubePosition = { 0.0f, 1.0f, -0.6f };
		
		Texture2D m_Texture;
		Texture2D m_DiffuseTexture;
	};

}