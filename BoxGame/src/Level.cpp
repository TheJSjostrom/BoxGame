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

        const Vector3 LeftDirection = { 0.0f, 0.0f, 1.0f };
        m_UpDirection = Vector3Normalize(Vector3CrossProduct(LeftDirection, m_Vector));
        
        if (IsKeyDown(KEY_KP_4))
        {
            m_VectorAngle += 180.0f * ts;
        }
        if (IsKeyDown(KEY_KP_6))
        {
            m_VectorAngle -= 180.0f * ts;
        }

        m_Vector.x = cos(radians(m_VectorAngle));
        m_Vector.y = sin(radians(m_VectorAngle));
        m_Vector.z = 0.0f;
        m_Vector = Vector3Normalize(m_Vector);
	}

	void Level::OnRender()
	{
        const Renderer& renderer = Application::GetRenderer();

        DrawLine3D({ 0.0f, 0.0f, 0.0f }, m_Vector, YELLOW);
        DrawLine3D({ 0.0f, 0.0f, 0.0f }, m_UpDirection, RED);

		m_Player.OnRender();

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
                            m_CubePosition, 6.0f, 6.0f, 2.0f, BLUE);

        renderer.RenderCube({ 0.0f,  renderer.GetTexture().height / 2.0f,
                    renderer.GetTexture().width / 2.0f,
                    renderer.GetTexture().height / 2.0f },
            { 4.0f, 3.0f, 0.0f }, 2.0f, 6.0f, 6.0f, BLUE);

		DrawGrid(100, 1.0f);
	}

}