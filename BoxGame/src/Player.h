#pragma once
#include "raylib.h"

namespace BoxGame {

	class Player
	{
	public:
		Player() = default;

		void OnUpdate(float ts);
		void OnRender();
	 
		const Vector3& GetPosition() const { return m_Position; }

	private:
		Vector3 m_Position = { -2.0f, 0.0f, -2.0f };
		float m_Angle = 0.0f;

		bool m_Jump = false;
		int m_JumpTimer = 0;
	};

}
 