#pragma once
#include "Game2D.h"
#include <ctime>
#include <stdlib.h>
#include "Setting.h"

namespace jm {
	class enemy
	{
	protected:
		int hp;
		int damage;
		int score;
		vec2 velocity;
		vec2 center = vec2(0.0f, 0.0f);

	public:
		enemy() {}
		enemy(int hp, int damage, vec2 velocity, int score) :hp(hp), damage(damage), velocity(velocity), score(score) {}
		virtual void update(const float& dt, vec2 direction) {}
		virtual void draw() {}

		int getHp() {
			return hp;
		}
		void setHp(int hp) {
			this->hp = hp;
		}
		int getDamage() {
			return damage;
		}
		void setDamage(int damage) {
			this->damage = damage;
		}
		vec2 getVelocity() {
			return this->velocity;
		}
		void setVelocity(vec2 velocity) {
			this->velocity = velocity;
		}
		vec2 getCenter() {
			return center;
		}
		void setCenter(vec2 center) {
			this->center = center;
		}

	};
}
