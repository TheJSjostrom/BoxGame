#include "Level.h"
#include "rlgl.h"

namespace BoxGame
{
	Level::Level()
	{
		m_Texture = LoadTexture("./res/Checkerboard.png");

		m_Model = LoadModel("./res/cat.glb");
		m_DiffuseTexture = LoadTexture("./res/backpack/diffuse2.png");
		m_Model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_DiffuseTexture;
	}

	void Level::OnUpdate(float ts)
	{
		m_Player.OnUpdate(ts);
	}

	void Level::OnRender()
	{
		m_Player.OnRender();
		//DrawModel(m_Model, { 1.0f, 0.0f, 0.0f }, 0.5f, WHITE);
		DrawModelWires(m_Model, { 0.0f, 0.0f, 0.0f }, 0.5f, WHITE);

		// X line
		DrawRay({ {0.0f, 0.0f, 0.0f},{ 1.0f, 0.0f, 0.0f} }, { 255, 0, 0, 255 });
		DrawRay({ {0.0f, 0.0f, 0.0f},{ -1.0f, 0.0f, 0.0f} }, WHITE);
		// Y line
		DrawRay({ {0.0f, 0.0f, 0.0f},{ 0.0f, 1.0f, 0.0f} }, { 0, 255, 0, 255 });
		DrawRay({ {0.0f, 0.0f, 0.0f}, { 0.0f, -1.0f, 0.0f} }, WHITE);
		// Z line
		DrawRay({ {0.0f, 0.0f, 0.0f},{ 0.0f, 0.0f, 1.0f} }, { 0, 0, 255, 255 });
		DrawRay({ {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, -1.0f} }, WHITE);

		DrawCubeTextureRec(m_Texture,
			{ 0.0f,  m_Texture.height / 2.0f,  m_Texture.width / 2.0f,  m_Texture.height / 2.0f },
			{ 1.0f, 0.5f, 0.0f }, 1.0f, 1.0f, 1.0f, WHITE);

		DrawGrid(100.0f, 1.0f);
	}

    void Level::DrawCubeTextureRec(Texture2D texture, Rectangle source, Vector3 position, float width, float height, float length, Color color)
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