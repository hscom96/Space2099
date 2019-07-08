#pragma once
#include "enemy.h"
#include "Game2D.h"

namespace jm {
	class SmallUFO : public enemy
	{
	public:
		SmallUFO() : enemy(200, 50, vec2(0.04f,0.04f), 50) {
			int flag1 = rand() % 2;
			int flag2 = rand() % 2;
			if (flag1 == 1) {
				float position_Y = (rand() / (float)RAND_MAX) * framesize_Y - framesize_Y / 2;
				//���ʺ��� ��ü����
				if (flag2 == 1)
					setCenter(vec2(-framesize_X / 2, position_Y));
				//�����ʺ��� ��ü����
				else
					setCenter(vec2(framesize_X / 2, position_Y));
			}
			else {
				float position_X = (rand() / (float)RAND_MAX) * framesize_X - framesize_X / 2;
				//���ʺ��� ��ü����
				if (flag2 == 1) {
					setCenter(vec2(position_X, framesize_Y / 2));
				}
				//�Ʒ��ʺ��� ��ü����
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
				if (GetDirectionLength(center, direction) < 1.6f) {
					float angle = GetDirectionAngle(center, direction);
					center.x += cos(angle * PI / 180) * velocity.x * dt;
					center.y += sin(angle * PI / 180) * velocity.y * dt;
				}
				else {
					center.x += ((rand() / (float)RAND_MAX) * framesize_X - framesize_X / 2) * velocity.x * dt;
					center.y += ((rand() / (float)RAND_MAX) * framesize_Y - framesize_Y / 2) * velocity.y * dt;

				}
			
		}
	};
}
