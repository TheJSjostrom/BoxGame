#include "raylib.h"

#include "src/Renderer.h"
#include "src/Application.h"
#include "src/Cube.h"
#include "raymath.h"

namespace BoxGame {

	Cube::Cube(const Vector3& position) : Player(position)
	{
	}

	void Cube::OnUpdate(const float ts)
	{
		Vector3 VectorDir = { 0.0f, 0.0f, 0.0f };

		if (IsKeyDown(KEY_UP))
		{
			VectorDir.z = -1.0f;
		}
		else if (IsKeyDown(KEY_DOWN))
		{
			VectorDir.z = 1.0f;
		}

		if (IsKeyDown(KEY_LEFT))
		{
			VectorDir.x = -1.0f;
		}
		else if (IsKeyDown(KEY_RIGHT))
		{
			VectorDir.x = 1.0f;
		}

		if (Vector3Length(VectorDir) > 0.0f)
		{
			const float speed = 5.0f;
			//VectorDir = Vector3Normalize(VectorDir);
			m_Velocity.z = VectorDir.z * speed;
			m_Velocity.x = VectorDir.x * speed;
		}

		// result = start + amount * (end - start);
		m_Velocity.x = Lerp(m_Velocity.x, 0.0f, 2.5f * ts);
		m_Velocity.z = Lerp(m_Velocity.z, 0.0f, 2.5f * ts);

		m_Position.x += m_Velocity.x * ts;
		m_Position.z += m_Velocity.z * ts;
	}

	void Cube::OnRender()
	{
		const Renderer& renderer = Application::GetRenderer();

		renderer.RenderCube(m_Position, 0.5f, 0.5f, 0.5f, ORANGE);

	}
}