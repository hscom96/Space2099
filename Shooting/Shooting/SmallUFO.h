#pragma once
#include "Enemy.h"
#include "Game2D.h"

namespace jm {
	class SmallUFO : public Enemy
	{
	public:
		SmallUFO() : Enemy(200, 1, vec2(0.04f, 0.04f), 50, 0.06f) {}

		virtual void draw() {
			beginTransformation();
			{
				translate(center.x, center.y);
				drawFilledCircle(Colors::gray, radius);
				drawFilledBox(Colors::darkgreen, 0.17f, 0.03f);
				translate(0, 0.09f);
				drawWiredBox(Colors::black, 0.2f, 0.03f);
				translate(-(0.2f-hp*0.001)/2, 0);
				drawFilledBox(Colors::red, hp*0.001, 0.03f);
			}
			endTransformation();
		}

		virtual void update(const float& dt, vec2 direction) {
			if (GetDirectionLength(center, direction) < 1.6f) {
				float angle = GetDirectionAngle(center, direction);
				center.x += cos(getRadian(angle)) * velocity.x * dt;
				center.y += sin(getRadian(angle)) * velocity.y * dt;
			}
			else {
				center.x += ((rand() / (float)RAND_MAX) * framesize_X - framesize_X / 2) * velocity.x * dt;
				center.y += ((rand() / (float)RAND_MAX) * framesize_Y - framesize_Y / 2) * velocity.y * dt;
			}

		}
	};
}
