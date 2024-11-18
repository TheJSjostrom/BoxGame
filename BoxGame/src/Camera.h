#pragma once
#include "raylib.h"

namespace BoxGame {

	class Camera
	{
	public:
		Camera();

		void SetPosition(const Vector3& position) { m_Camera.position = position; }
		const Vector3& GetPosition() { return m_Camera.position; }

		void SetTarget(const Vector3& target) { m_Camera.target = target; }
		const Vector3& GetTarget() { return m_Camera.target; }

		void SetFov(float fov) { m_Camera.fovy = fov; }
		float GetFov() { return m_Camera.fovy; }

		Camera3D& GetCamera() { return m_Camera; }

	private:
		Camera3D m_Camera;
	};

}
 