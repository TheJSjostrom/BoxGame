#pragma once
#include <iostream>

namespace BoxGame {

	class Menu
	{
	public:
		virtual ~Menu() = default;

		virtual void OnUpdate(float ts) = 0;
		virtual void OnRender() = 0;
	};

}