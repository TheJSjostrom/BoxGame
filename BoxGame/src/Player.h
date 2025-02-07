#pragma once

namespace BoxGame {

	class Player
	{
	public:
		Player(const Vector3& position) : m_Position(position), m_Velocity({ 0.0f, 0.0f, 0.0f })
		{
			int x = 2;
		}

		virtual ~Player()
		{
			int x = 2;
		}

		virtual void OnUpdate(const float tp) = 0;
		virtual void OnRender() = 0;

	protected:
		Vector3 m_Position;
		Vector3 m_Velocity;
	};

}