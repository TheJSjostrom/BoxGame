#pragma once
#include "raylib.h"

namespace BoxGame {

	class Mesh
	{
	public:
		Mesh() = default;

		void Init();

		void OnUpdate(const float ts);
		void OnRender();

	private:
		Vector3 m_ModelTarget = { 0.0f, 0.0f, 0.0f };
		Vector3 m_FrontDirection = { 0.0f, 0.0f, -1.0f };
		Vector3 m_Position = { 0.0f, 0.0f, 0.0f };

		Model m_Model;

		float ModelRotationAngle = 90.0f;
		float m_FrontDirectionAngle = 0.0f;
	};

}
 