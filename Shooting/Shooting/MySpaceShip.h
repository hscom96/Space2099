#pragma once
#include "Game2D.h"
#include "Setting.h"

namespace jm {
	class MySpaceShip
	{
	private :
		float radius;
	public:
		MySpaceShip() :radius(0.06f) {}
		vec2 center = vec2(0.0f, 0.0f);
		vec2 direction = vec2(1.0f, 0.0f); 
		void draw();
		void update(char key, const float& dt) {
			switch (key) {
			case GLFW_KEY_A:
				center.x -= 0.15f * dt;
				break;
			case GLFW_KEY_D:
				center.x += 0.15f * dt;
				break;
			case GLFW_KEY_W:
				center.y += 0.15f * dt;
				break;
			case GLFW_KEY_S:
				center.y -= 0.15f * dt;
				break;
			}
		}
		float getRadius() {
			return radius;
		}
		vec2 getCenter() {
			return center;
		}
	};
}