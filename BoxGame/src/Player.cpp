#include "src/Player.h"
#include "raymath.h"

namespace BoxGame {

	static float radians(float degrees)
	{
		return degrees * (PI / 180);
	}

	void Player::OnUpdate(float ts)
	{
	
		m_Jump = true;
		

		if (m_Jump)
		{
			m_JumpTimer += 1;

			if (m_JumpTimer < 80)
			{
				m_Position.y += 2 * ts;
			}
			else
			{
				m_Position.y -= 2 * ts;
			}
		}

		if (m_JumpTimer >= 160)
		{
			m_JumpTimer = 0;
			m_Jump = false;
			m_Position.y = 0.25f;
		}
	}

	void Player::OnRender()
	{
		DrawSphere({ m_Position.x, m_Position.y + 0.5f, m_Position.z }, 0.25f, BLACK);
		DrawSphereWires({ m_Position.x,m_Position.y + 0.5f, m_Position.z }, 0.25f, 50, 50, BLUE);
		DrawCube(m_Position, 0.5f, 0.5f, 0.5f, BLACK);
		DrawCubeWires(m_Position, 0.503f, 0.503f, 0.503f, BLUE);
	}

}