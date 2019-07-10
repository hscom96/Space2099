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
				drawFilledCircle(Colors::gray, radius); //우주선본체
				drawFilledBox(Colors::darkgreen, 0.17f, 0.03f); //우주선가운데 
				translate(0, radius + 0.03f);
				drawWiredBox(Colors::black, 0.2f, 0.03f); //체력바
				translate(-(0.2f-hp*0.001)/2, 0);
				drawFilledBox(Colors::red, hp*0.001, 0.03f); //체력게이지
			}
			endTransformation();
		}

	
	};
}
