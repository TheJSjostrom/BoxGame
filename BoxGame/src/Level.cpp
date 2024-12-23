#include <iostream>

#include "math.h"
#include "src/Level.h"
#include "src/Renderer.h"
#include "src/Application.h"

#include "rlgl.h"
#include "raymath.h"

namespace BoxGame
{
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
        m_Player.Init();   
	}

	void Level::OnUpdate(float ts)
	{
		m_Player.OnUpdate(ts);

        if (IsKeyDown(KEY_Z))
        {
            m_Angle += 180.0f * ts;
        }
       if (IsKeyDown(KEY_X))
        {
            m_Angle -= 180.0f * ts;
        }

        m_Vec.x = cos(radians(m_Angle)) * 1.0f;
        m_Vec.z = 0.0f;
        m_Vec.y = sin(radians(m_Angle)) * 1.0f;

        log(m_Angle);

        const Vector3 UpDirection = { 0.0f, 1.0f, 0.0f };
        m_LeftDirection = Vector3Normalize(Vector3CrossProduct(UpDirection, m_Vec));
	}

	void Level::OnRender()
	{
        Renderer& renderer = Application::GetRenderer();
        
		m_Player.OnRender();

        DrawLine3D({0.0f, 0.0f, 0.0f}, m_Vec, BLACK);
        DrawLine3D({ 0.0f, 0.0f, 0.0f }, m_LeftDirection, YELLOW);

        // Rendering m_Vec's vector components
        DrawLine3D({ m_Vec.x, 0.0f, 0.0f }, m_Vec, DARKBLUE);
        DrawLine3D({ 0.0f, 0.0f, 0.0f }, { m_Vec.x, 0.0f, 0.0f }, DARKBLUE);

		// X line
		DrawRay({ {0.0f, 0.0f, 0.0f},{ 1.0f, 0.0f, 0.0f} }, { 255, 0, 0, 255 });
		DrawRay({ {0.0f, 0.0f, 0.0f},{ -1.0f, 0.0f, 0.0f} }, WHITE);
		// Y line
		DrawRay({ {0.0f, 0.0f, 0.0f},{ 0.0f, 1.0f, 0.0f} }, { 0, 255, 0, 255 });
		DrawRay({ {0.0f, 0.0f, 0.0f}, { 0.0f, -1.0f, 0.0f} }, WHITE);
		// Z line
		DrawRay({ {0.0f, 0.0f, 0.0f},{ 0.0f, 0.0f, 1.0f} }, { 0, 0, 255, 255 });
		DrawRay({ {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, -1.0f} }, WHITE);

        renderer.RenderCube({ 0.0f,  renderer.GetTexture().height / 2.0f,
                            renderer.GetTexture().width / 2.0f, 
                            renderer.GetTexture().height / 2.0f },
                            m_CubePosition, 3.0f, 3.0f, 1.0f, WHITE);

        renderer.RenderCube({ 0.0f,  renderer.GetTexture().height / 2.0f,
                    renderer.GetTexture().width / 2.0f,
                    renderer.GetTexture().height / 2.0f },
            {4.0f, 1.0f, 0.0f }, 3.0f, 3.0f, 3.0f, BLUE);

		DrawGrid(100, 1.0f);
	}

}