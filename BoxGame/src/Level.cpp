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
		m_Train.Init();   
	}

	void Level::OnUpdate(float ts)
	{
		m_Train.OnUpdate(ts);

		Vector3 VectorDir = { 0.0f, 0.0f, 0.0f };

		if (IsKeyDown(KEY_Y))
		{
			VectorDir.z = -1.0f;
		}
		else if (IsKeyDown(KEY_H))
		{
			VectorDir.z = 1.0f;
		}

		if (IsKeyDown(KEY_G))
		{
			VectorDir.x = -1.0f;
		}
		else if (IsKeyDown(KEY_J))
		{
			VectorDir.x = 1.0f;
		}

		if (Vector3Length(VectorDir) > 0.0f)
		{
			const float speed = 5.0f;
			VectorDir = Vector3Normalize(VectorDir);
			m_Velocity.z = VectorDir.z * speed;
			m_Velocity.x = VectorDir.x * speed;
		}

		// result = start + amount*(end - start);
		m_Velocity.x = Lerp(m_Velocity.x, 0.0f, 2.5f * ts);
		m_Velocity.z = Lerp(m_Velocity.z, 0.0f, 2.5f * ts);

		m_Position.x += m_Velocity.x * ts;
		m_Position.z += m_Velocity.z * ts;
	}

	void Level::OnRender()
	{
        const Renderer& renderer = Application::GetRenderer();

		m_Train.OnRender();
		
		renderer.RenderCube(m_Position, 0.5f, 0.5f, 0.5f, SKYBLUE);

		DrawLine3D({ 0.0f, 0.0f, 0.0f }, m_Velocity, YELLOW);

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