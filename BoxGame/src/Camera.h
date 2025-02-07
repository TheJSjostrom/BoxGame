#pragma once
#include "raylib.h"

namespace BoxGame {

	class Camera
	{
	public:
		Camera();

		void OnUpdate(float ts);

		const Vector3& GetPosition() const { return m_Camera.position; }
		const Vector3& GetTarget() const { return m_Camera.target; }
		const Camera3D& GetCamera() const { return m_Camera; }

	private:
		void OnUpdateCamera();

	private:
		Camera3D m_Camera;

		Vector3 m_FrontDirection = { 0.0f, 0.0f, 1.0f };
		Vector3 m_Target = { 0.0f, 0.0f, 0.0f };
		Vector3 m_Position = { -3.0f, 1.0f, 3.0f };

		bool m_FirstFrame = true;
		float m_Yaw = -45.0f;
		float m_Pitch = 0.0f;
		float m_LastXPosition = 640.0f;
		float m_LastYPosition = 0.0f;
		float m_CameraSpeed = 5.0f;

		bool m_First = false;
	};

}
 