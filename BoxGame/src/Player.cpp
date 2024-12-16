#include <iostream>

#include "src/Player.h"

#include "raymath.h"
 
namespace BoxGame {

	static float radians(float degrees)
	{
		return degrees * (PI / 180);
	}

	void Player::Init()
	{
		m_Model = LoadModel("./res/cat.glb");
	}

	void Player::OnUpdate(float ts)
	{
		m_Model.transform = MatrixRotateY(radians(m_Angle + 90.0f));

		Vector3 UpDirection = { 0.0f, 1.0f, 0.0f };
		Vector3 LeftDirection = Vector3Normalize(Vector3CrossProduct(UpDirection, m_FrontDirection));

		if (IsKeyDown(KEY_RIGHT))
		{
			m_Angle -= 180.0f * ts;
		}
		if (IsKeyDown(KEY_LEFT))
		{
			m_Angle += 180.0f * ts;
		}

		if (IsKeyDown(KEY_UP))
		{
			m_Position.x += m_FrontDirection.x * 5.0f * ts;
			m_Position.z += m_FrontDirection.z * 5.0f * ts;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			m_Position.x -= m_FrontDirection.x * 5.0f * ts;
			m_Position.z -= m_FrontDirection.z * 5.0f * ts;
		}

		m_FrontDirection.x += cos(radians(-m_Angle)) * 1;
		m_FrontDirection.y += 0.0f;
		m_FrontDirection.z += sin(radians(-m_Angle)) * 1;
		m_FrontDirection = Vector3Normalize(m_FrontDirection);

		m_ModelTarget.x = m_Position.x + m_FrontDirection.x;
		m_ModelTarget.y = m_Position.y + m_FrontDirection.y;
		m_ModelTarget.z = m_Position.z + m_FrontDirection.z;
	}

	void Player::OnRender()
	{
		DrawLine3D({ m_Position.x, 0.0f, m_Position.z }, { m_ModelTarget.x, 0.0f, m_ModelTarget.z}, DARKBLUE);
		DrawModelWires(m_Model, m_Position, 0.5f, WHITE);
	}

}