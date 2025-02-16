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
		Model m_Model;

		Vector3 m_ModelTarget = { 0.0f, 0.0f, 0.0f };
		Vector3 m_FrontDirection = { 0.0f, 0.0f, -1.0f };
		Vector3 m_Position = { 0.0f, 0.0f, 0.0f };
	};

}
 