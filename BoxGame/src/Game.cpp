#include "Game.h"
#include <math.h>
#include <iostream>
#include "raymath.h"
#include "raylib.h"
#include "Application.h"

namespace BoxGame {

	Game::Game()
	{
		DisableCursor();
		m_StartTarget = { 0.0f, 0.0f, 0.0f };
		m_EndTarget = { 0.0f, 0.0f, 0.0f };

		m_StartPos = { 0.0f, 0.0f, 0.0f };
		m_EndPos = { 0.0f, 0.0f, 0.0f };

		m_StartCamDir = { 0.0f, 0.0f, 0.0f };
		m_EndCamDir = { 0.0f, 0.0f, 0.0f };	 

		Image image = LoadImage("../res/skybox/Checkerboard.png");
		m_Texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}

	void Game::OnUpdate(float ts)
	{
		m_Camera.OnUpdate(ts);
		m_Player.OnUpdate(ts);

		m_EndTarget = m_Camera.GetTarget();
		m_EndPos = m_Camera.GetPosition();
		m_EndPos.y -= 1.0f;
 
		m_StartCamDir = m_EndPos;
		m_StartCamDir.y -= 1.0f;
		m_EndCamDir = m_EndTarget;
	}

	void Game::OnRender()
	{
		BeginMode3D(m_Camera.GetCamera());
		// X line
		DrawLine3D({ 0.0f, 0.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }, RED);
		DrawLine3D({ 0.0f, 0.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, WHITE);
		// Y line
		DrawLine3D({ 0.0f, 0.0f, 0.0f }, { 0.0f, 10.0f, 0.0f }, GREEN);
		DrawLine3D({ 0.0f, 0.0f, 0.0f }, { 0.0f, -10.0f, 0.0f }, WHITE);
		// Z line
		DrawLine3D({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 10.0f }, BLUE);
		DrawLine3D({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -10.0f }, WHITE);
		
		// Render Position Vector - Target Vector - Camera Direction Vector
		//DrawLine3D(m_StartPos, m_EndPos, RED);
		DrawLine3D(m_StartTarget, m_EndTarget, YELLOW);
		DrawLine3D(m_StartCamDir, m_EndCamDir, BLUE);

		// Render Platform
		DrawCube({ 0.0f, 0.125f, 0.0f }, 2.0f, 0.25f, 2.0f, DARKGRAY);
		DrawCubeWires({ 0.0f, 0.125f, 0.0f }, 2.0f, 0.25f, 2.0f, GRAY);

		// Render Cubes
		DrawCube({ 2.0f, 0.25f, -2.0f }, 0.5f, 0.5f, 0.5f, BLACK);
		DrawCubeWires({ 2.0f, 0.25f, -2.0f }, 0.503f, 0.503f, 0.503f, GREEN);

		DrawCube({ 2.0f, 0.25f, 2.0f }, 0.5f, 0.5f, 0.5f, BLACK);
		DrawCubeWires({ 2.0f, 0.25f, 2.0f }, 0.503f, 0.503f, 0.503f, RED);

		DrawCube({ -2.0f, 0.25f, 2.0f }, 0.5f, 0.5f, 0.5f, BLACK);
		DrawCubeWires({ -2.0f, 0.25f, 2.0f }, 0.503f, 0.503f, 0.503f, YELLOW);

		// Render Spheres
		DrawSphere({ 2.0f, 0.75f, -2.0f }, 0.25f, BLACK);
		DrawSphereWires({ 2.0f, 0.75f, -2.0f }, 0.25f, 50, 50, GREEN);
		DrawSphere({ 2.0f, 0.75f, 2.0f }, 0.25f, BLACK);
		DrawSphereWires({ 2.0f, 0.75f, 2.0f }, 0.25f, 50, 50, RED);
		DrawSphere({ -2.0f, 0.75f, 2.0f }, 0.25f, BLACK);
		DrawSphereWires({ -2.0f, 0.75f, 2.0f }, 0.25f, 50, 50, YELLOW);

		DrawGrid(10.0f, 0.75f);
		m_Player.OnRender();
		EndMode3D();

		DrawTexture(m_Texture, Application::Get().GetWindow().GetWidth() / 2 - m_Texture.width / 2, Application::Get().GetWindow().GetHeight() / 2 - m_Texture.height / 2, WHITE);
	}

}