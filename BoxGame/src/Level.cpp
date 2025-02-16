#include <iostream>

#include "math.h"
#include "src/Level.h"
#include "src/Renderer.h"
#include "src/Application.h"

#include "rlgl.h"
#include "raymath.h"

namespace BoxGame {

    static void log(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    static void log(float message)
    {
        std::cout << message << std::endl;
    }

	// From degrees to radians.
	static float radians(float degrees)
	{
		return degrees * (PI / 180);
	}


	Vector3 RotationMatrix(const Vector3& vector, float angle)
	{
		Vector3 v;
		v.x = vector.x * cos(radians(angle)) - vector.y * sin(radians(angle));
		v.y = vector.x * sin(radians(angle)) + vector.y * cos(radians(angle));
		v.z = 0.0f;
		return v;
	}

	Level::Level()
	{
		m_Player = std::make_unique<Cube>(Vector3{ 6.0f, 0.25f, 0.0f });
		//m_Train.Init();

		m_Quad.VectorA = { cos(radians(45.0f)), sin(radians(45.0f)), 0.0f };
		m_Quad.VectorA = Vector3Normalize(m_Quad.VectorA);

		m_Quad.VectorB = { cos(radians(135.0f)), sin(radians(135.0f)), 0.0f };
		m_Quad.VectorB = Vector3Normalize(m_Quad.VectorB);

		m_Quad.VectorC = { cos(radians(225.0f)), sin(radians(225.0f)), 0.0f };
		m_Quad.VectorC = Vector3Normalize(m_Quad.VectorC);

		m_Quad.VectorD = { cos(radians(315.0f)), sin(radians(315.0f)), 0.0f };
		m_Quad.VectorD = Vector3Normalize(m_Quad.VectorD);
	}

	void Level::OnUpdate(const float ts)
	{
		const Vector2 MousePosition = GetMousePosition();
		const float CurrentXPosition = MousePosition.x;

		if (m_FirstFrame)
		{
			m_LastXPosition = CurrentXPosition;
			m_FirstFrame = false;
		}

		const float OffsetX = CurrentXPosition - m_LastXPosition;
		m_LastXPosition = CurrentXPosition;

		const float sensitivity = 0.125f;
		m_Cube.Angle += OffsetX * sensitivity;

		if (IsKeyDown(KEY_L))
		{
			m_Cube.Angle += 180.0f * ts;
		}
		else if (IsKeyDown(KEY_J))
		{
			m_Cube.Angle -= 180.0f * ts;
		}

		Vector3 direction;
		direction.x = cos(radians(m_Cube.Angle));
		direction.y = 0.0f;
		direction.z = sin(radians(m_Cube.Angle));
		direction = Vector3Normalize(direction);

		if (IsMouseButtonDown(0) || IsKeyPressed(KEY_I))
		{
			m_Cube.Position.x += direction.x * ts;
			m_Cube.Position.z += direction.z * ts;
		}
		else if (IsMouseButtonDown(1) || IsKeyPressed(KEY_K))
		{
			m_Cube.Position.x -= direction.x * ts;
			m_Cube.Position.z -= direction.z * ts;
		}

		m_Cube.Direction.x = direction.x + m_Cube.Position.x;
		m_Cube.Direction.y = 0.0f;
		m_Cube.Direction.z = direction.z + m_Cube.Position.z;

		m_Player->OnUpdate(ts);
		//m_Train.OnUpdate(ts);
		m_IceBlock.OnUpdate(ts);

		if (IsKeyDown(KEY_X))
		{
			m_Quad.Angle += 180.0f * ts;
		}
		else if (IsKeyDown(KEY_C))
		{
			m_Quad.Angle -= 180.0f * ts;
		}

		m_Quad.FrontDirection.x = cos(radians(m_Quad.Angle));
		m_Quad.FrontDirection.y = sin(radians(m_Quad.Angle));
		m_Quad.FrontDirection.z = 0.0f;
	
		const float speed = 5.0f;

		if (IsKeyDown(KEY_T))
		{
			m_Quad.Position.x += m_Quad.FrontDirection.x * ts;
			m_Quad.Position.y += m_Quad.FrontDirection.y * ts;
			m_Quad.Position.z += 0.0f;

			m_Quad.Start.x += m_Quad.FrontDirection.x * ts;
			m_Quad.Start.y += m_Quad.FrontDirection.y * ts;
			m_Quad.Start.z += m_Quad.FrontDirection.z * ts;
		}
		if (IsKeyDown(KEY_F))
		{
			m_Quad.Position.x -= m_Quad.FrontDirection.x * ts;
			m_Quad.Position.y -= m_Quad.FrontDirection.y * ts;
			m_Quad.Position.z -= 0.0f;

			m_Quad.Start.x -= m_Quad.FrontDirection.x * ts;
			m_Quad.Start.y -= m_Quad.FrontDirection.y * ts;
			m_Quad.Start.z -= m_Quad.FrontDirection.z * ts;
		}

		m_Quad.RotatedVectorA.x = m_Quad.VectorA.x * cos(radians(m_Quad.Angle)) - m_Quad.VectorA.y * sin(radians(m_Quad.Angle)) + m_Quad.Position.x;
		m_Quad.RotatedVectorA.y = m_Quad.VectorA.x * sin(radians(m_Quad.Angle)) + m_Quad.VectorA.y * cos(radians(m_Quad.Angle)) + m_Quad.Position.y;
		m_Quad.RotatedVectorA.z = 0.0f;
		
		m_Quad.RotatedVectorB.x = m_Quad.VectorB.x * cos(radians(m_Quad.Angle)) - m_Quad.VectorB.y * sin(radians(m_Quad.Angle)) + m_Quad.Position.x;
		m_Quad.RotatedVectorB.y = m_Quad.VectorB.x * sin(radians(m_Quad.Angle)) + m_Quad.VectorB.y * cos(radians(m_Quad.Angle)) + m_Quad.Position.y;
		m_Quad.RotatedVectorB.z = 0.0f;
		 
		m_Quad.RotatedVectorC.x = m_Quad.VectorC.x * cos(radians(m_Quad.Angle)) - m_Quad.VectorC.y * sin(radians(m_Quad.Angle)) + m_Quad.Position.x;
		m_Quad.RotatedVectorC.y = m_Quad.VectorC.x * sin(radians(m_Quad.Angle)) + m_Quad.VectorC.y * cos(radians(m_Quad.Angle)) + m_Quad.Position.y;
		m_Quad.RotatedVectorC.z = 0.0f;
	
		m_Quad.RotatedVectorD.x = m_Quad.VectorD.x * cos(radians(m_Quad.Angle)) - m_Quad.VectorD.y * sin(radians(m_Quad.Angle)) + m_Quad.Position.x;
		m_Quad.RotatedVectorD.y = m_Quad.VectorD.x * sin(radians(m_Quad.Angle)) + m_Quad.VectorD.y * cos(radians(m_Quad.Angle)) + m_Quad.Position.y;
		m_Quad.RotatedVectorD.z = 0.0f;
		
	}
	
	void Level::OnRender()
	{
        const Renderer& renderer = Application::GetRenderer();
		
		renderer.RenderLine(m_Quad.Start, { m_Quad.FrontDirection.x + m_Quad.Position.x, m_Quad.FrontDirection.y + m_Quad.Position.y, 0.0f }, PURPLE);

		renderer.RenderLine(m_Quad.Start, m_Quad.RotatedVectorA, PURPLE);
		renderer.RenderLine(m_Quad.Start, m_Quad.RotatedVectorB, PURPLE);
		renderer.RenderLine(m_Quad.Start, m_Quad.RotatedVectorC, PURPLE);
		renderer.RenderLine(m_Quad.Start, m_Quad.RotatedVectorD, PURPLE);

		renderer.RenderLine(m_Quad.RotatedVectorA, m_Quad.RotatedVectorB, PURPLE);
		renderer.RenderLine(m_Quad.RotatedVectorB, m_Quad.RotatedVectorC, PURPLE);
		renderer.RenderLine(m_Quad.RotatedVectorC, m_Quad.RotatedVectorD, PURPLE);
		renderer.RenderLine(m_Quad.RotatedVectorD, m_Quad.RotatedVectorA, PURPLE);

		renderer.RenderLine({ m_Cube.Position.x, 0.0f, m_Cube.Position.z }, m_Cube.Direction, WHITE);
		renderer.RenderLine({ 0.0f, 0.0f, 0.0f }, m_Cube.Position, GREEN);

		renderer.RenderCube({ m_Cube.Position.x, 0.25f, m_Cube.Position.z }, 0.5f, 0.5f, 0.5f, GOLD);

		m_Player->OnRender();
		//m_Train.OnRender();
		m_IceBlock.OnRender();

		// X line
		renderer.RenderRay({ 0.0f, 0.0f, 0.0f }, Vector3Normalize({ 1.0f, 0.0f, 0.0f }), { 255, 0, 0, 255 });
		renderer.RenderRay({ 0.0f, 0.0f, 0.0f }, Vector3Normalize({ -1.0f, 0.0f, 0.0f }), WHITE);

		// Y line
		renderer.RenderRay({ 0.0f, 0.0f, 0.0f }, Vector3Normalize({ 0.0f, 1.0f, 0.0f }), { 0, 255, 0, 255 });
		renderer.RenderRay({ 0.0f, 0.0f, 0.0f }, Vector3Normalize({ 0.0f, -1.0f, 0.0f }), WHITE);
	
		// Z line
		renderer.RenderRay({ 0.0f, 0.0f, 0.0f }, Vector3Normalize({ 0.0f, 0.0f, 1.0f }), { 0, 0, 255, 255 });
		renderer.RenderRay({ 0.0f, 0.0f, 0.0f }, Vector3Normalize({ 0.0f, 0.0f, -1.0f }), WHITE);

        renderer.RenderTextureRec(renderer.GetBricketWallTexture(), {0.0f, renderer.GetBricketWallTexture().height * 2.0f,
                            renderer.GetBricketWallTexture().width * 2.0f,
                            renderer.GetBricketWallTexture().height * 2.0f },
                            m_CubePosition, 6.0f, 6.0f, 2.0f, DARKGRAY);
	
        renderer.RenderTextureRec(renderer.GetCheckerBoardTexture(), {0.0f, renderer.GetCheckerBoardTexture().height * 50.0f,
								   renderer.GetCheckerBoardTexture().width * 50.0f,
                                   renderer.GetCheckerBoardTexture().height * 50.0f },
			{ 0.0f, -0.505f, 0.0f }, 100.0f, 1.0f, 100.0f, { 5, 18, 45, 255 });
		
		renderer.RenderTextureCube(renderer.GetWoodTexture(), { 1.0f, 0.25f, -2.75f }, 0.5f, 0.5f, 0.5f, GRAY);
		renderer.RenderTextureCube(renderer.GetWoodTexture(), { 1.0f, 0.25f, 1.0f }, 0.5f, 0.5f, 0.5f, GRAY);
		//DrawGrid(100, 1.0f);
	}

}