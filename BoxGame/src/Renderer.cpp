#include <iostream>

#include "raylib.h"
#include "rlgl.h"

#include "src/Renderer.h"

namespace BoxGame {

    Renderer::Renderer()
    {
       Init();
    }

    Renderer::~Renderer()
    {
        Shutdown();
    }

    void Renderer::Init()
    {
        m_Texture = LoadTexture("./res/Wooden.png");
        m_Texture2 = LoadTexture("./res/Checkerboard.png");
        m_Texture3 = LoadTexture("./res/bricketwall.png");

        m_PauseButton = LoadTexture("./res/PauseButton.png");
        m_PlayButton = LoadTexture("./res/PlayButton.png");

        if (!IsTextureReady(m_Texture))
        {
            std::cout << "The m_Texture texture couldn't initialize successfully" << std::endl;
        } 
        else if (!IsTextureReady(m_Texture2))
        {
            std::cout << "The m_Texture2 texture couldn't initialize successfully" << std::endl;
        }
        else if (!IsTextureReady(m_Texture3))
        {
            std::cout << "The m_Texture3 texture couldn't initialize successfully" << std::endl;
        }
        else if (!IsTextureReady(m_PauseButton))
        {
            std::cout << "The m_PauseButton texture couldn't initialize successfully" << std::endl;
        }
        else if (!IsTextureReady(m_PlayButton))
        {
            std::cout << "The m_PlayButton texture couldn't initialize successfully" << std::endl;
        }
    }

    void Renderer::Shutdown()
    {
        UnloadTexture(m_Texture);
        UnloadTexture(m_Texture2);
        UnloadTexture(m_Texture3);

        UnloadTexture(m_PauseButton);
        UnloadTexture(m_PlayButton);
    }

    void Renderer::RenderText(const std::string& text, uint32_t xPos, uint32_t yPos, uint32_t fontSize, const Color& color) const
    {
		DrawText(text.c_str(), xPos, yPos, fontSize, color);
    }

    void Renderer::RenderIceBlock(const Vector3& position, float width, float height, float length, const Color& color) const
    {
        DrawCube(position, width, height, length, color);
    }

    void Renderer::RenderLine(const Vector3& startPos, const Vector3& endPos, const Color& color) const
    {
        DrawLine3D(startPos, endPos, color);
    }

    void Renderer::RenderCube(const Vector3& position, float width, float height, float length, const Color& color) const
    {
        DrawCube(position, width, height, length, color);
    }

    void Renderer::RenderRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const Color& color) const
    {
        DrawRectangle(x, y, width, height, color);
    }

    void Renderer::RenderRay(const Vector3& position, const Vector3& direction, const Color& color) const
    {
        DrawRay({ position, direction }, color);
    }

    void Renderer::RenderTexture(const Texture2D& texture, uint32_t XPos, uint32_t YPos, const Color& color) const
    {
        DrawTexture(texture, XPos, YPos, color);
    }

    void Renderer::RenderTextureCube(const Texture2D& texture, const Vector3& position, float width, float height, float length, const Color& color) const
    {
        float x = position.x;
        float y = position.y;
        float z = position.z;

        // Set desired texture to be enabled while drawing following vertex data
        rlSetTexture(texture.id);

        // Vertex data transformation can be defined with the commented lines,
        // but in this example we calculate the transformed vertex data directly when calling rlVertex3f()
        //rlPushMatrix();
            // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
            //rlTranslatef(2.0f, 0.0f, 0.0f);
            //rlRotatef(45, 0, 1, 0);
            //rlScalef(2.0f, 2.0f, 2.0f);

        rlBegin(RL_QUADS);
        rlColor4ub(color.r, color.g, color.b, color.a);
        // Front Face
        rlNormal3f(0.0f, 0.0f, 1.0f);       // Normal Pointing Towards Viewer
        rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
        rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
        // Back Face
        rlNormal3f(0.0f, 0.0f, -1.0f);     // Normal Pointing Away From Viewer
        rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
        rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
        // Top Face
        rlNormal3f(0.0f, 1.0f, 0.0f);       // Normal Pointing Up
        rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        // Bottom Face
        rlNormal3f(0.0f, -1.0f, 0.0f);     // Normal Pointing Down
        rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        // Right face
        rlNormal3f(1.0f, 0.0f, 0.0f);       // Normal Pointing Right
        rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z - length / 2);  // Bottom Right Of The Texture and Quad
        rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z - length / 2);  // Top Right Of The Texture and Quad
        rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width / 2, y + height / 2, z + length / 2);  // Top Left Of The Texture and Quad
        rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width / 2, y - height / 2, z + length / 2);  // Bottom Left Of The Texture and Quad
        // Left Face
        rlNormal3f(-1.0f, 0.0f, 0.0f);    // Normal Pointing Left
        rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z - length / 2);  // Bottom Left Of The Texture and Quad
        rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width / 2, y - height / 2, z + length / 2);  // Bottom Right Of The Texture and Quad
        rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z + length / 2);  // Top Right Of The Texture and Quad
        rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width / 2, y + height / 2, z - length / 2);  // Top Left Of The Texture and Quad
        rlEnd();
        //rlPopMatrix();

        rlSetTexture(0);
    }


	void Renderer::RenderTextureRec(const Texture2D& testure, const Rectangle& source, const Vector3& position, float width, float height, float length, const Color& color) const
	{
        float x = position.x;
        float y = position.y;
        float z = position.z;
        float texWidth = (float)testure.width;
        float texHeight = (float)testure.height;

        // Set desired texture to be enabled while drawing following vertex data
        rlSetTexture(testure.id);

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