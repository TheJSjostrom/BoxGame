#include "Player.h"
#include "raymath.h"

namespace BoxGame {

	static float radians(float degrees)
	{
		return degrees * (PI / 180);
	}

	void Player::OnUpdate(float ts)
	{
	}

	void Player::OnRender()
	{
		DrawSphere({ m_Position.x, 0.75f, m_Position.z }, 0.25f, BLACK);
		DrawSphereWires({ m_Position.x, 0.75f, m_Position.z }, 0.25f, 50, 50, BLUE);
		DrawCube(m_Position, 0.5f, 0.5f, 0.5f, BLACK);
		DrawCubeWires(m_Position, 0.503f, 0.503f, 0.503f, BLUE);
	}

}