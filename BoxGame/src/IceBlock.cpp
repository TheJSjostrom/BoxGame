#include "raylib.h"
#include "raymath.h"

#include "src/Renderer.h"
#include "src/Application.h"
#include "src/IceBlock.h"

namespace BoxGame {

	void IceBlock::OnUpdate(float ts)
	{
		Vector3 VectorDir = { 0.0f, 0.0f, 0.0f };

		if (IsKeyDown(KEY_KP_8))
		{
			VectorDir.z = -1.0f;
		}
		else if (IsKeyDown(KEY_KP_5))
		{
			VectorDir.z = 1.0f;
		}

		if (IsKeyDown(KEY_KP_4))
		{
			VectorDir.x = -1.0f;
		}
		else if (IsKeyDown(KEY_KP_6))
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

		m_VectorDir.z = m_Velocity.z + m_Position.z;
		m_VectorDir.x = m_Velocity.x + m_Position.x;
	}

	void IceBlock::OnRender()
	{
		const Renderer& renderer = Application::GetRenderer();
		
		renderer.RenderIceBlock(m_Position, m_Dimension, m_Dimension, m_Dimension);
		DrawCubeWiresV(m_Position, { m_Dimension, m_Dimension, m_Dimension }, WHITE);
		renderer.RenderLine({ m_Position.x, m_Position.y - 0.25f, m_Position.z }, m_VectorDir, YELLOW);
	}

}