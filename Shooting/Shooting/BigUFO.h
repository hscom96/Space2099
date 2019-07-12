#pragma once
#include "Enemy.h"
#include "Game2D.h"

namespace jm {
	class BigUFO : public Enemy
	{
	public:
		BigUFO() : Enemy(300, 2, vec2(0.04f, 0.04f), 80, 0.1f) {}

		virtual void draw() {
			beginTransformation();
			{
				translate(center.x, center.y);
				drawFilledCircle(Colors::skyblue, radius); //우주선본체
				drawFilledBox(Colors::purple, radius*2+0.05f, 0.03f); //우주선가운데 
				translate(0, radius + 0.03f);
				drawWiredBox(Colors::black, 0.3f, 0.03f); //체력바
				translate(-(0.3f - hp * 0.001) / 2, 0);
				drawFilledBox(Colors::red, hp * 0.001, 0.03f); //체력게이지
			}
			endTransformation();
		}


	};
}
