#include <iostream>

#include "src/Mesh.h"

#include "raymath.h"
 
namespace BoxGame {

	static float radians(float degrees)
	{
		return degrees * (PI / 180);
	}

	void Mesh::Init()
	{
		m_Model = LoadModel("./res/lok.glb");
	}

	void Mesh::OnUpdate(float ts)
	{
		m_Model.transform = MatrixRotateY(radians(ModelRotationAngle));
		const float speed = 5.0f;

		// Change ModelAngle and FrontVectorAngle
		if (IsKeyDown(KEY_RIGHT))
		{
			m_FrontDirectionAngle += 180.0f * ts;
			ModelRotationAngle -= 180.0f * ts;
		}
		else if (IsKeyDown(KEY_LEFT))
		{
			m_FrontDirectionAngle -= 180.0f * ts;
			ModelRotationAngle += 180.0f * ts;
		}

		if (IsKeyDown(KEY_UP))
		{
			m_Position.x += m_FrontDirection.x * speed * ts;
			m_Position.z += m_FrontDirection.z * speed * ts;
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			m_Position.x -= m_FrontDirection.x * speed * ts;
			m_Position.z -= m_FrontDirection.z * speed * ts;
		}

		m_FrontDirection.x = cos(radians(m_FrontDirectionAngle));
		m_FrontDirection.y = 0.0f;
		m_FrontDirection.z = sin(radians(m_FrontDirectionAngle));
		m_FrontDirection = Vector3Normalize(m_FrontDirection);

		m_ModelTarget.x = m_Position.x + m_FrontDirection.x;
		m_ModelTarget.y = m_Position.y + m_FrontDirection.y;
		m_ModelTarget.z = m_Position.z + m_FrontDirection.z;
	}

	void Mesh::OnRender()
	{
		DrawLine3D({ m_Position.x, 0.0f, m_Position.z }, { m_ModelTarget.x, 0.0f, m_ModelTarget.z}, DARKBLUE);
		DrawModelWires(m_Model, m_Position, 0.01f, WHITE);
	}

}