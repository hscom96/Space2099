#pragma once
#include "Game2D.h"
#include "Setting.h"
#include "Weapon.h"

namespace jm {
	class MyBullet :public Weapon
	{
	public:

		MyBullet() : Weapon(0.2f, 50) {}
		virtual void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			endTransformation();
		}
		virtual void update(const float& dt)
		{
			center.x += cos(getRadian(angle)) * velocity.x * dt;
			center.y += sin(getRadian(angle)) * velocity.y * dt;
		}


	};
}