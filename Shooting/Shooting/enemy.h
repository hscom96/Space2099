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
		Enemy(int hp, int damage, vec2 velocity, int score, float radius) :hp(hp), damage(damage), velocity(velocity), score(score), radius(radius) {
			int flag1 = rand() % 2;
			int flag2 = rand() % 2;
			float position_Y;
			float position_X;

			switch (flag1) {
			case 1:
				position_Y = (rand() / (float)RAND_MAX) * framesize_Y - framesize_Y / 2;
				switch (flag2) {
				case 1: //哭率寒俊 按眉积己
					setCenter(vec2(-framesize_X / 2, position_Y));
					break;

				case 0: //坷弗率寒俊 按眉积己
					setCenter(vec2(framesize_X / 2, position_Y));
					break;
				}
			case 0:
				position_X = (rand() / (float)RAND_MAX) * framesize_X - framesize_X / 2;
				switch (flag2) {

				case 1://困率寒俊 按眉积己 
					setCenter(vec2(position_X, framesize_Y / 2));
					break;
				case 0://酒贰率寒俊 按眉积己
					setCenter(vec2(position_X, -framesize_Y / 2));
					break;
				}
			}
		}
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
