#pragma once
#include "Camera.h"
#include "Player.h"
#include "Level.h"

namespace BoxGame {

	class Game
	{
	public:
		Game();

		void OnUpdate(float ts);
		void OnRender();

	private:
		Camera m_Camera;
		Level m_Level;
	};

}
