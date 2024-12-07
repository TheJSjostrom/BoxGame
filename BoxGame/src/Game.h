#pragma once
#include "src/Camera.h"
#include "src/Player.h"
#include "src/Level.h"

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
