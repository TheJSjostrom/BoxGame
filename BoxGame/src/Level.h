#pragma once
#include "raylib.h"
#include "Player.h"

namespace BoxGame {

	class Level
	{
	public:
		Level();

		void OnUpdate(float ts);
		void OnRender();

	private:
		void DrawCubeTextureRec(Texture2D texture, Rectangle source, Vector3 position, float width, float height, float length, Color color);

	private:
		Player m_Player;

		Model m_Model;
		Texture2D m_Texture;
		Texture2D m_DiffuseTexture;
	};

}