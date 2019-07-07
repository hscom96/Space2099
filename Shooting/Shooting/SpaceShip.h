#pragma once
#include<iostream>
#include "Game2D.h"
#include "math.h"
#include "SmallUFO.h"
#include "Setting.h"

namespace jm
{
	class MySpaceShip
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 direction = vec2(1.0f, 0.0f); //회전


		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledBox(Colors::orange, 0.15f, 0.12f); // body
			translate(0.03, 0.06f);
			drawFilledBox(Colors::green, 0.25f, 0.02f); //shooter
			translate(0, -0.12f);
			drawFilledBox(Colors::green, 0.25f, 0.02f); //shooter2
			translate(0.07f, 0.06f);
			rotate(270.0f);
			drawFilledTriangle(Colors::darkRed, 0.095f); // head
			endTransformation();


		}
	};

	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 direction = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);
		float angle;

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


	class SpaceShip : public Game2D
	{
	public:
		MySpaceShip spaceship;
		SmallUFO smallufo[40];

		MyBullet* bullet1 = nullptr;
		MyBullet* bullet2 = nullptr;
		std::vector<MyBullet*> bullet_Container; // 총알을 담는 컨테이너
		float timer; // 총알 타이머
		float delay; //총알 딜레이


	public:
		SpaceShip() :timer(0), delay(100) {
		}

		~SpaceShip()
		{
			if (bullet1 != nullptr) {
				delete bullet1;
				delete bullet2;
			}
		}

		void update() override
		{


			// 우주선움직임
			if (isKeyPressed(GLFW_KEY_A))  spaceship.center.x -= 0.15f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_D))	spaceship.center.x += 0.15f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_W))	spaceship.center.y += 0.15f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_S))	spaceship.center.y -= 0.15f * getTimeStep();
			spaceship.direction = getCursorPos();

			// 총알생성
			if (this->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			{
				//총알타이머
				timer += getTimeStep();
				//총알타이머 딜레이도달시
				if (timer >= delay * getTimeStep()) {
					//첫번쨰 무기에서 나가는 총알 생성
					bullet1 = new MyBullet;
					bullet1->center = spaceship.center;
					bullet1->center.y += 0.08f;
					bullet1->velocity = vec2(0.20f, 0.20f);
					bullet1->direction = getCursorPos();
					bullet1->angle = GetDirectionAngle(bullet1->center, bullet1->direction);
					bullet_Container.push_back(bullet1);

					//두번쨰 무기에서 나가는 총알 생성
					bullet2 = new MyBullet;
					bullet2->center = spaceship.center;
					bullet2->center.y -= 0.08f;
					bullet2->velocity = vec2(0.20f, 0.20f);
					bullet2->direction = getCursorPos();
					bullet2->angle = GetDirectionAngle(bullet2->center, bullet2->direction);
					bullet_Container.push_back(bullet2);

					timer = 0; // 타이머 초기화
				}
			}

			std::vector<MyBullet*>::iterator it; //총알 컨테이너 반복자
			//총알이동
			if (bullet_Container.empty() != true) {
				for (it = bullet_Container.begin(); it != bullet_Container.end(); it++) {
					(*it)->update(getTimeStep());
				}
			}

			//총알 rendering
			if (bullet_Container.empty() != true) {
				beginTransformation();
				{
					for (it = bullet_Container.begin(); it != bullet_Container.end(); it++) {
						(*it)->draw();
					}
				}
				endTransformation();
			}
			// 마우스 조준점 rendering	
			beginTransformation();
			{
				translate(getCursorPos());
				setLineWidth(4.0f);
				drawWiredCircle(Colors::red, 0.07f);
				drawLine(Colors::red, vec2(-0.07f, 0), Colors::red, vec2(+0.07f, 0));
				drawLine(Colors::red, vec2(0, -0.07f), Colors::red, vec2(0, +0.07f));
			}
			endTransformation();

			//우주선 rendering
			beginTransformation();
			{
				translate(spaceship.center.x, spaceship.center.y);
				rotate(GetDirectionAngle(spaceship.center, spaceship.direction));
				translate(-spaceship.center.x, -spaceship.center.y);
				spaceship.draw();
			}
			endTransformation();

			//작은 UFO rendering
			beginTransformation();
			{
				srand(static_cast<size_t>(time(NULL)));
				for (int i = 0; i < 40; i++) {
					smallufo[i].draw();
				}
			}
			endTransformation();

			// 불필요한 총알 삭제
			if (bullet_Container.size() >= 14) {
				MyBullet::deleteBullet(bullet_Container);
			}
		}

	};
}