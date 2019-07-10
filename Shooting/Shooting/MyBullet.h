#pragma once
#include "Game2D.h"
#include "Setting.h"
#include "Weapon.h"

namespace jm {
	class MyBullet :public Weapon
	{
	public:

		MyBullet() : Weapon(0.02f) {}
		virtual void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, radius, 8);
			drawWiredRegularConvexPolygon(Colors::gray, radius, 8);
			endTransformation();
		}
		virtual void update(const float& dt)
		{
			center.x += cos(getRadian(angle)) * velocity.x * dt;
			center.y += sin(getRadian(angle)) * velocity.y * dt;
		}


	};
}