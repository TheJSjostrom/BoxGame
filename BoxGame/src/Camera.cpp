#include <iostream>

#include "src/Camera.h"

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

	Camera::Camera()
	{
		m_Camera.position = { 0.0f, 0.0f, 0.0f };
		m_Camera.target = { 0.0f, 0.0f, 0.0f };
		m_Camera.up = { 0.0f, 1.0f, 0.0f };
		m_Camera.fovy = 45.0f;
		m_Camera.projection = CAMERA_PERSPECTIVE;
	}

	void Camera::OnUpdate(const float ts)
	{
		const Vector3 UpDirection = { 0.0f, 1.0f, 0.0f };
		const Vector3 LeftDirection = Vector3Normalize(Vector3CrossProduct(UpDirection, m_FrontDirection));

		Vector2 CurrentMousePosition = GetMousePosition();
		float CurrentXPosition = CurrentMousePosition.x;
		float CurrentYPosition = CurrentMousePosition.y;

		if (m_FirstFrame)
		{
			m_LastXPosition = CurrentXPosition;
			m_LastYPosition = CurrentYPosition;
			m_FirstFrame = false;
		}

		float OffsetX = CurrentXPosition - m_LastXPosition;
		m_LastXPosition = CurrentXPosition;

		float OffsetY = m_LastYPosition - CurrentYPosition;
		m_LastYPosition = CurrentYPosition;

		m_Yaw += OffsetX * 0.05f;
		m_Pitch += OffsetY * 0.05f;
	
		if (m_Pitch > 89.0f)
		{
			m_Pitch = 89.0f;
		}
		else if (m_Pitch < -89.0f)
		{
			m_Pitch = -89.0f;
		}

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

		if (IsKeyDown(KEY_A))
		{
			m_Position.x += LeftDirection.x * m_CameraSpeed * ts;
			m_Position.y += LeftDirection.y * m_CameraSpeed * ts;
			m_Position.z += LeftDirection.z * m_CameraSpeed * ts;

		}

		if (IsKeyDown(KEY_D))
		{
			m_Position.x -= LeftDirection.x * m_CameraSpeed * ts;
			m_Position.y -= LeftDirection.y * m_CameraSpeed * ts;
			m_Position.z -= LeftDirection.z * m_CameraSpeed * ts;
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

		OnUpdateCamera();
	}

	void Camera::OnUpdateCamera()
	{
		m_Target.x = m_FrontDirection.x + m_Position.x;
		m_Target.y = m_FrontDirection.y + m_Position.y;
		m_Target.z = m_FrontDirection.z + m_Position.z;

		m_Camera.position = m_Position;
		m_Camera.target = m_Target;
	}

}
 