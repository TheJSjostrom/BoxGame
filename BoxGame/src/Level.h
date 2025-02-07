#pragma once
#include <array>
#include "raylib.h"

#include "src/IceBlock.h"
#include "src/Mesh.h"
#include "src/Cube.h"

namespace BoxGame {

	struct Entity
	{
		Vector3 Position = { 0.0f, 0.0f, 0.0f };
		Vector3 Direction = { 0.0f, 0.0f, 0.0f };
		float Angle = 0.0f;
	};

	class Level
	{
	public:
		Level();
		~Level() = default;

		void OnUpdate(const float ts);
		void OnRender();

	private:
		Mesh m_Train;
		IceBlock m_IceBlock;

		std::unique_ptr<Player> m_Player;

		Vector3 m_CubePosition = { 0.0f, 3.0f, -4.0f };

		Entity m_Cube;

		bool m_FirstFrame = true;
		float m_LastXPosition = 0.0f;
	};

}