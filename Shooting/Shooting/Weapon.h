#pragma once
#include "Game2D.h"
namespace jm {
	class Weapon {
	protected:
		float radius;
		float angle;
		int damage;

	public:
		Weapon(float radius, int damage) :radius(radius), damage(damage) {}
		vec2 center;
		vec2 direction;
		vec2 velocity;

		virtual void draw() {};
		virtual void update(const float& dt) {};

		void setAngle(float angle) {
			if (0.0f <= angle && angle <= 360.0f) {
				this->angle = angle;
			}
		}

		float getRadius() {
			return radius;
		}

		int getDamage() {
			return damage;
		}
	};
}