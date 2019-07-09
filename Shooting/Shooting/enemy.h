#pragma once
#include "Game2D.h"
#include <ctime>
#include <stdlib.h>
#include "Setting.h"

namespace jm {
	class Enemy
	{
	protected:
		int hp;
		int damage;
		int score;
		float radius;

		vec2 velocity;
		vec2 center = vec2(0.0f, 0.0f);

	public:
		Enemy() {}
		Enemy(int hp, int damage, vec2 velocity, int score, float radius) :hp(hp), damage(damage), velocity(velocity), score(score), radius(radius) {}
		virtual void update(const float& dt, vec2 direction) {}
		virtual void draw() {}

		int getScore() {
			return score;
		}
		float getRadius() {
			return radius;
		}

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
