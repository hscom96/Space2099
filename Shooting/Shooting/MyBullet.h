#pragma once
#include "Game2D.h"
#include "Setting.h"

namespace jm {
	class MyBullet
	{
	private:
		float radius;
		float angle;
		float damage;
		float delay;
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 direction = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);

		MyBullet() :radius(0.2f), damage(0), delay(50.f){}
		MyBullet(float radius, float damage) : radius(radius), damage(damage) {};

		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			endTransformation();
		}

		void update(const float& dt)
		{
			center.x += cos(angle * PI / 180) * velocity.x * dt;
			center.y += sin(angle * PI / 180) * velocity.y * dt;
		}

		void setAngle(float angle) {
			if (0.0f <= angle && angle <= 360.0f) {
				this->angle = angle;
			}
		}


		//불필요한총알 삭제
		static void deleteBullet(std::vector<MyBullet*>& bullet_Container) {
			std::vector<MyBullet*>::iterator it; //총알 컨테이너 반복자
			for (it = bullet_Container.begin(); it != bullet_Container.end();) {
				MyBullet* temp = *it;   // 임시변수
				if (abs(temp->center.x) > framesize_X || abs(temp->center.y) > framesize_Y)
				{
					if (temp != nullptr)  // nullptr검사후 메모리해제하기.
						delete temp;
					temp = nullptr;
					it = bullet_Container.erase(it);
					if (bullet_Container.size() == 0)  // 컨테이너사이즈가 0이면 더 돌필요없이 종료
						break;
				}
				else {
					it++;
				}
			}
		}
	};
}