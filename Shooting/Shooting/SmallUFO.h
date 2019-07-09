#pragma once
#include "Enemy.h"
#include "Game2D.h"

namespace jm {
	class SmallUFO : public Enemy
	{
	public:
		SmallUFO() : Enemy(200, 1, vec2(0.04f, 0.04f), 50, 0.06f) {
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

		void draw() {
			beginTransformation();
			{
				translate(center.x, center.y);
				drawFilledCircle(Colors::gray, 0.06f);
				drawFilledBox(Colors::darkgreen, 0.17, 0.03);
			}
			endTransformation();
		}

		void update(const float& dt, vec2 direction) {
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
