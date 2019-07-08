#pragma once
#include "Game2D.h"
#include "Setting.h"

namespace jm {
	class MySpaceShip
	{
	private:
		float delay;
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 direction = vec2(1.0f, 0.0f); //È¸Àü
		MySpaceShip(float delay) :delay(delay) {}
		void draw();
		void update();
		float getDelay() {
			return delay;
		}
	};
}