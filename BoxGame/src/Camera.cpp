#include "Camera.h"
#include <iostream>

namespace BoxGame {

	Camera::Camera()
	{
		m_Camera.position = { 0.0f, 0.0f, 0.0f };
		m_Camera.target = { 0.0f, 0.0f, 0.0f };
		m_Camera.up = { 0.0f, 1.0f, 0.0f };
		m_Camera.fovy = 45.0f;
		m_Camera.projection = CAMERA_PERSPECTIVE;
	}

}
 