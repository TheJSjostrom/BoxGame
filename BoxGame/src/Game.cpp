#include "Game.h"
#include <math.h>
#include <iostream>
#include "raymath.h"
namespace BoxGame {

	// From degrees to radians.
	static float Radians(float degrees)
	{
		return degrees * (PI / 180);
	}

	Game::Game()
	{
		m_StartTarget = { 0.0f, 0.0f, 0.0f };
		m_EndTarget = { 0.0f, 0.0f, 0.0f };

		m_StartPos = { 0.0f, 0.0f, 0.0f };
		m_EndPos = { 0.0f, 0.0f, 0.0f };

		m_StartCamDir = { 0.0f, 0.0f, 0.0f };
		m_EndCamDir = { 0.0f, 0.0f, 0.0f };	

	
		m_Image = LoadImage("assets\skybox\back.jpg");
		m_Texture = LoadTextureFromImage(m_Image);
	}

	void Game::OnUpdate(float ts)
	{
		//UpdateCamera(&m_Camera.GetCamera(), m_Camera.GetCamera().projection);	

		float MouseXPos = (float)GetMouseX();
		float MouseYPos = (float)GetMouseY();

		if (m_FirstRender)
		{
			m_LastMouseX = MouseXPos;
			m_LastMouseY = MouseYPos;
			m_FirstRender = false;
		}

		float OffsetX = MouseXPos - m_LastMouseX;
		m_LastMouseX = MouseXPos;
		
		float OffsetY = m_LastMouseY - MouseYPos;
		m_LastMouseY = MouseYPos;

		m_Yaw += OffsetX * 0.25f;
		m_Pitch += OffsetY * 0.25f;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		Vector3 CameraDir;
		CameraDir.x = cos(Radians(m_Yaw)) * cos(Radians(m_Pitch));
		CameraDir.y = sin(Radians(m_Pitch));
		CameraDir.z = sin(Radians(m_Yaw)) * cos(Radians(m_Pitch));
		Vector3 CameraDirectionNor = Vector3Normalize(CameraDir);

		Vector3 FrontDir;
		FrontDir.x = cos(Radians(m_Yaw));
		FrontDir.y = 0.0f;
		FrontDir.z = sin(Radians(m_Yaw));
		Vector3 LeftSideDir = Vector3CrossProduct({ 0.0f, 1.0f, 0.0f }, FrontDir);

		if (IsKeyDown(KEY_W))
		{
			m_Position.x += CameraDirectionNor.x * m_PositionSpeed * ts;
			m_Position.y += CameraDirectionNor.y * m_PositionSpeed * ts;
			m_Position.z += CameraDirectionNor.z * m_PositionSpeed * ts;
		}
		if (IsKeyDown(KEY_S))
		{ 
			m_Position.x -= CameraDirectionNor.x * m_PositionSpeed * ts;
			m_Position.y -= CameraDirectionNor.y * m_PositionSpeed * ts;
			m_Position.z -= CameraDirectionNor.z * m_PositionSpeed * ts;
		}
		if (IsKeyDown(KEY_D))
		{
			m_Position.x -= LeftSideDir.x * m_PositionSpeed * ts;
			m_Position.z -= LeftSideDir.z * m_PositionSpeed * ts;
		}
		if (IsKeyDown(KEY_A))
		{
			m_Position.x += LeftSideDir.x * m_PositionSpeed * ts;
			m_Position.z += LeftSideDir.z * m_PositionSpeed * ts;
		}

		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			m_PositionSpeed = 50.0f;
		}
		if (!IsKeyDown(KEY_LEFT_SHIFT))
		{
			m_PositionSpeed = 5.0f;
		}

		m_Target.x = CameraDirectionNor.x + m_Position.x;
		m_Target.y = CameraDirectionNor.y + m_Position.y;
		m_Target.z = CameraDirectionNor.z + m_Position.z;

		if (IsKeyDown(KEY_Q))
			m_Fov += 1.0f;
		if (IsKeyDown(KEY_E))
			m_Fov -= 1.0f;
		if (IsKeyDown(KEY_R))
			m_Fov = 45.0f;
	
		m_Camera.SetFov(m_Fov);
		m_Camera.SetTarget(m_Target);
		m_Camera.SetPosition(m_Position);
		 
		m_EndTarget = m_Camera.GetTarget();
		m_EndPos = m_Camera.GetPosition();
		m_EndPos.y -= 1.0f;
 
		m_StartCamDir = m_EndPos;
		m_StartCamDir.y -= 1.0f;
		m_EndCamDir = m_EndTarget;

		m_Player.OnUpdate(ts);
	}

	void Game::OnRender()
	{
		DrawTexture(m_Texture, 10, 10, WHITE);
		BeginMode3D(m_Camera.GetCamera());
		// X line
		DrawLine3D({ 0.0f, 0.0f, 0.0f }, {10.0f, 0.0f, 0.0f}, RED);
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
		//DrawCube({ 0.0f, -0.25f, 0.0f }, 4.0f, 0.5f, 4.0f, DARKGRAY);
		//DrawCubeWires({ 0.0f, -0.25f, 0.0f }, 4.0f, 0.5f, 4.0f, GRAY);

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
	}

}