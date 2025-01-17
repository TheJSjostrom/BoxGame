#pragma once

#include "raylib.h"

#include "src/IceBlock.h"
#include "src/Mesh.h"

namespace BoxGame {

	class Level
	{
	public:
		Level();

		void OnUpdate(float ts);
		void OnRender();

	private:
		Mesh m_Train;
		IceBlock m_IceBlock;

		Vector3 m_Vector = { 1.0f, 0.0f, 0.0f };
		float m_VectorAngle = 45.0f;
		Vector3 m_UpDirection = { 0.0f, 0.0f, 0.0f };

		Vector3 m_CubePosition = { 0.0f, 3.0f, -4.0f };
	
		float m_Angle = 0.0f;

		bool m_Play = true;
	};

}