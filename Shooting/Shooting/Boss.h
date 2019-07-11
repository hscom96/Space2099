#pragma once
#include "Enemy.h"
#include "Game2D.h"

namespace jm {
	class Boss : public Enemy{

	public:
		Boss() : Enemy(1500, 2, vec2(0.03f, 0.03f), 200, 0.4f) {}

		virtual void draw() {
			beginTransformation();
			{
				translate(center.x, center.y);
				drawFilledCircle(Colors::orange, radius); //우주선 
				drawFilledBox(Colors::olive, 2*radius+0.1f, 0.05f); //우주선본체
				translate(0, radius + 0.03f);
				drawWiredBox(Colors::black, 1.5f, 0.03f); //체력바
				translate(-(1.5f - hp * 0.001) / 2, 0);
				drawFilledBox(Colors::red, hp * 0.001f, 0.03f); //체력 게이지
			}
			endTransformation();
		}
	};
}