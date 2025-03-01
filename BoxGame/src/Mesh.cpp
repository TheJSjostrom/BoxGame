#include <iostream>

#include "src/Mesh.h"

#include "raymath.h"
 
namespace BoxGame {

	static float radians(float degrees)
	{
		return degrees * (PI / 180);
	}

	void Mesh::Init()
	{
		m_Model = LoadModel("./res/lok.glb");
	}

	void Mesh::OnUpdate(const float ts)
	{
	}

	void Mesh::OnRender()
	{
		DrawLine3D({ m_Position.x, 0.0f, m_Position.z }, { m_ModelTarget.x, 0.0f, m_ModelTarget.z}, DARKBLUE);
		DrawModelWires(m_Model, m_Position, 0.01f, WHITE);
	}

}