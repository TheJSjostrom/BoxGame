#pragma once

namespace BoxGame {

	class IceBlock
	{
	public:
		void OnUpdate(const float ts);
		void OnRender();

	private:
		Vector3 m_Position = { 4.0f, 0.25f, 0.0f };
		Vector3 m_Velocity = { 0.0f, 0.0f, 0.0f };
		Vector3 m_VectorDir = { 0.0f, 0.0f, 0.0f };

		float m_Dimension = 0.5f;
	};

}