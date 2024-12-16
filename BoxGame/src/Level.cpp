#include <iostream>

#include "math.h"
#include "src/Level.h"

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

        m_Texture = LoadTexture("./res/Checkerboard.png");
		m_DiffuseTexture = LoadTexture("./res/backpack/diffuse2.png");
		
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
		m_Player.OnRender();

        DrawLine3D({0.0f, 0.0f, 0.0f}, m_Vec, BLACK);
        DrawLine3D({ 0.0f, 0.0f, 0.0f }, m_LeftDirection, YELLOW);

        // Rendering m_Vec's vector components
        DrawLine3D({ m_Vec.x, 0.0f, 0.0f }, m_Vec, DARKBLUE);
        DrawLine3D({ 0.0f, 0.0f, 0.0f }, { m_Vec.x, 0.0f, 0.0f }, DARKBLUE);

		// X line
	//	DrawRay({ {0.0f, 0.0f, 0.0f},{ 1.0f, 0.0f, 0.0f} }, { 255, 0, 0, 255 });
	//	DrawRay({ {0.0f, 0.0f, 0.0f},{ -1.0f, 0.0f, 0.0f} }, WHITE);
		// Y line
		DrawRay({ {0.0f, 0.0f, 0.0f},{ 0.0f, 1.0f, 0.0f} }, { 0, 255, 0, 255 });
		DrawRay({ {0.0f, 0.0f, 0.0f}, { 0.0f, -1.0f, 0.0f} }, WHITE);
		// Z line
		DrawRay({ {0.0f, 0.0f, 0.0f},{ 0.0f, 0.0f, 1.0f} }, { 0, 0, 255, 255 });
		DrawRay({ {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, -1.0f} }, WHITE);

		DrawCubeTextureRec(m_Texture,
			{ 0.0f,  m_Texture.height / 2.0f,  m_Texture.width / 2.0f,  m_Texture.height / 2.0f },
			m_CubePosition, 3.0f, 3.0f, 1.0f, WHITE);

		DrawGrid(100, 1.0f);
	}

    void Level::DrawCubeTextureRec(const Texture2D& texture, const Rectangle& source, const Vector3& position, float width, float height, float length, const Color& color)
    {
        float x = position.x;
        float y = position.y;
        float z = position.z;
        float texWidth = (float)texture.width;
        float texHeight = (float)texture.height;

        // Set desired texture to be enabled while drawing following vertex data
        rlSetTexture(texture.id);

        // We calculate the normalized texture coordinates for the desired texture-source-rectangle
        // It means converting from (tex.width, tex.height) coordinates to [0.0f, 1.0f] equivalent 
        rlBegin(RL_QUADS);
        rlColor4ub(color.r, color.g, color.b, color.a);

        // Front face
        rlNormal3f(0.0f, 0.0f, 1.0f);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);

        // Back face
        rlNormal3f(0.0f, 0.0f, -1.0f);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);

        // Top face
        rlNormal3f(0.0f, 1.0f, 0.0f);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);

        // Bottom face
        rlNormal3f(0.0f, -1.0f, 0.0f);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);

        // Right face
        rlNormal3f(1.0f, 0.0f, 0.0f);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z - length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x + width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x + width / 2, y - height / 2, z + length / 2);

        // Left face
        rlNormal3f(-1.0f, 0.0f, 0.0f);
        rlTexCoord2f(source.x / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z - length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, (source.y + source.height) / texHeight);
        rlVertex3f(x - width / 2, y - height / 2, z + length / 2);
        rlTexCoord2f((source.x + source.width) / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z + length / 2);
        rlTexCoord2f(source.x / texWidth, source.y / texHeight);
        rlVertex3f(x - width / 2, y + height / 2, z - length / 2);

        rlEnd();

        rlSetTexture(0);
    }
}