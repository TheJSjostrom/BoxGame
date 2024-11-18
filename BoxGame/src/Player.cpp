#include "Player.h"
#include <math.h>

namespace BoxGame {

	void Player::OnUpdate(float ts)
	{
		if (IsKeyDown(KEY_UP))
		{
			m_Position.z += 5.0f * ts;	
		}
		if (IsKeyDown(KEY_DOWN))
		{
			m_Position.z -= 5.0f * ts;
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			m_Position.x -= 5.0f * ts;
		}
		if (IsKeyDown(KEY_LEFT))
		{
			m_Position.x += 5.0f * ts;
		}
	}

	void Player::OnRender()
	{
		DrawSphere({ m_Position.x, 0.75f, m_Position.z }, 0.25f, BLACK);
		DrawSphereWires({ m_Position.x, 0.75f, m_Position.z }, 0.25f, 50, 50, BLUE);
		DrawCube(m_Position, 0.5f, 0.5f, 0.5f, BLACK);
		DrawCubeWires(m_Position, 0.503f, 0.503f, 0.503f, BLUE);
	}
}