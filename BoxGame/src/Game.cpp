#include "Game.h"
#include <math.h>
#include <iostream>
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

	Game::Game()
	{
		DisableCursor();
		m_StartTarget = { 0.0f, 0.0f, 0.0f };
		m_EndTarget = { 0.0f, 0.0f, 0.0f };

		m_StartPos = { 0.0f, 0.0f, 0.0f };
		m_EndPos = { 0.0f, 0.0f, 0.0f };

		m_StartCamDir = { 0.0f, 0.0f, 0.0f };
		m_EndCamDir = { 0.0f, 0.0f, 0.0f };	

		m_FrontDirection = { 0.0f, 0.0f, -1.0f };
	}

	void Game::OnUpdate(float ts)
	{
		Vector3 UpDirection = { 0.0f, 1.0f, 0.0f };
		Vector3 LeftDirection = Vector3Normalize(Vector3CrossProduct(UpDirection, m_FrontDirection));
		log(Vector3Length(LeftDirection));

		Vector2 MousePosition = GetMousePosition();
		float MouseXPos = MousePosition.x;
		float MouseYPos = MousePosition.y;
		
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

		Vector3 frontDirection;
		frontDirection.x = cos(radians(m_Yaw)) * cos(radians(m_Pitch));
		frontDirection.y = sin(radians(m_Pitch));
		frontDirection.z = sin(radians(m_Yaw)) * cos(radians(m_Pitch));
		m_FrontDirection = Vector3Normalize(frontDirection);

		if (IsKeyDown(KEY_W))
		{
			m_Position.x += m_FrontDirection.x * m_CameraSpeed * ts;
			m_Position.y += m_FrontDirection.y * m_CameraSpeed * ts;
			m_Position.z += m_FrontDirection.z * m_CameraSpeed * ts;
		}
		if (IsKeyDown(KEY_S))
		{ 
			m_Position.x -= m_FrontDirection.x * m_CameraSpeed * ts;
			m_Position.y -= m_FrontDirection.y * m_CameraSpeed * ts;
			m_Position.z -= m_FrontDirection.z * m_CameraSpeed * ts;
		}
		if (IsKeyDown(KEY_D))
		{
			m_Position.x -= LeftDirection.x * m_CameraSpeed * ts;
			m_Position.y -= LeftDirection.y * m_CameraSpeed * ts;
			m_Position.z -= LeftDirection.z * m_CameraSpeed * ts;
		}
		if (IsKeyDown(KEY_A))
		{
			m_Position.x += LeftDirection.x * m_CameraSpeed * ts;
			m_Position.y += LeftDirection.y * m_CameraSpeed * ts;
			m_Position.z += LeftDirection.z * m_CameraSpeed * ts;
		}
		if (IsKeyDown(KEY_Q))
		{
			m_Position.x += UpDirection.x * m_CameraSpeed * ts;
			m_Position.y += UpDirection.y * m_CameraSpeed * ts;
			m_Position.z += UpDirection.z * m_CameraSpeed * ts;
		}
		if (IsKeyDown(KEY_E))
		{
			m_Position.x -= UpDirection.x * m_CameraSpeed * ts;
			m_Position.y -= UpDirection.y * m_CameraSpeed * ts;
			m_Position.z -= UpDirection.z * m_CameraSpeed * ts;
		}

		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			m_CameraSpeed = 50.0f;
		}
		if (!IsKeyDown(KEY_LEFT_SHIFT))
		{
			m_CameraSpeed = 5.0f;
		}

		m_Target.x = m_FrontDirection.x + m_Position.x;
		m_Target.y = m_FrontDirection.y + m_Position.y;
		m_Target.z = m_FrontDirection.z + m_Position.z;
	
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