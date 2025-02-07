#pragma once
#include <string>
#include "src/Player.h"

namespace BoxGame {

	class Cube: public Player
	{
	public:
		Cube(const Vector3& position);
		~Cube();

		virtual void OnUpdate(const float ts) override;
		virtual void OnRender() override;
	};

}