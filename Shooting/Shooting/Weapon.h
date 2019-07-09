#pragma once
#include "Game2D.h"
namespace jm {
	class Weapon {
	protected:
		float radius;
		float angle;
		int damage;
		vec2 center;
		vec2 direction;
		vec2 velocity;
		
	public:
		Weapon(float radius, int damage) :radius(radius), damage(damage) {}

		virtual void draw() {};
		virtual void update(const float& dt) {};

		void setAngle(float angle) {
			if (0.0f <= angle && angle <= 360.0f) {
				this->angle = angle;
			}
		}

		vec2 getCenter() {
			return center;
		}
		void setCenter(vec2 center){
			this->center = center;
		}

		void setVelocity(vec2 velocity) {
			this->velocity = velocity;
		}
		vec2 getDirection() {
			return direction;
		}
		void setDirection(vec2 direction) {
			this->direction = direction;
		}
		float getRadius() {
			return radius;
		}

		int getDamage() {
			return damage;
		}
	};
}