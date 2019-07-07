#pragma once
#include "entity.h"
#include "Game2D.h"

namespace jm {
	class SmallUFO : public entity
	{
	public:
		SmallUFO() : entity(200, 50, vec2(), 50) {
			int flag1 = rand() % 2;
			int flag2 = rand() % 2;
			if (flag1 == 1) {
				float position_Y = (rand() / (float)RAND_MAX) * framesize_Y - framesize_Y / 2;
				//哭率寒俊 按眉积己
				if (flag2 == 1)
					setCenter(vec2(-framesize_X / 2, position_Y));
				//坷弗率寒俊 按眉积己
				else
					setCenter(vec2(framesize_X / 2, position_Y));
			}
			else {
				float position_X = (rand() / (float)RAND_MAX) * framesize_X - framesize_X / 2;
				//困率寒俊 按眉积己
				if (flag2 == 1) {
					setCenter(vec2(position_X, framesize_Y / 2));
				}
				//酒贰率寒俊 按眉积己
				else {
					setCenter(vec2(position_X, -framesize_Y / 2));
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
			float angle = GetDirectionAngle(center, direction);
			center.x += cos(angle * PI / 180) * velocity.x * dt;
			center.y += sin(angle * PI / 180) * velocity.y * dt;
		}
	};
}
