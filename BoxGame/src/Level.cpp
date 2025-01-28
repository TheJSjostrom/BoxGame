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

	Level::Level()
	{
		m_Player = std::make_unique<Cube>(Vector3{ 6.0f, 0.25f, 0.0f });
		m_Train.Init();
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

		if (IsMouseButtonPressed(0) || IsKeyPressed(KEY_I))
		{
			m_Cube.Position.x += direction.x;
			m_Cube.Position.z += direction.z;
		}
		else if (IsMouseButtonPressed(1) || IsKeyPressed(KEY_K))
		{
			m_Cube.Position.x -= direction.x;
			m_Cube.Position.z -= direction.z;
		}
	
		m_Cube.Direction.x = direction.x + m_Cube.Position.x;
		m_Cube.Direction.y = 0.0f;
		m_Cube.Direction.z = direction.z + m_Cube.Position.z;

		m_Player->OnUpdate(ts);
		//m_Train.OnUpdate(ts);
		m_IceBlock.OnUpdate(ts);
	}

	void Level::OnRender()
	{
        const Renderer& renderer = Application::GetRenderer();

		renderer.RenderLine({ m_Cube.Position.x, 0.0f, m_Cube.Position.z }, m_Cube.Direction, BLUE);
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

        renderer.RenderTextureCube({ 0.0f, renderer.GetTexture().height / 2.0f,
                            renderer.GetTexture().width / 2.0f, 
                            renderer.GetTexture().height / 2.0f },
                            m_CubePosition, 6.0f, 6.0f, 2.0f, BLUE);

        renderer.RenderTextureCube({ 0.0f, renderer.GetTexture().height / 2.0f,
                    renderer.GetTexture().width / 2.0f,
                    renderer.GetTexture().height / 2.0f },
					{ 4.0f, 3.0f, 0.0f }, 2.0f, 6.0f, 6.0f, BLUE);

		DrawGrid(100, 1.0f);
	}

}