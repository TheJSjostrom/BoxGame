#pragma once
#include "raylib.h"

namespace BoxGame {

	class Player
	{
	public:
		Player() = default;

		void OnUpdate(float ts);
		void OnRender();
	 
		const Vector3& GetPosition() { return m_Position; }

	private:
		Vector3 m_Position = { -2.0f, 0.25f, -2.0f };
	};

}
 