#pragma once
#include<iostream>
#include "Game2D.h"
#include "math.h"
#include "SmallUFO.h"
#include "Setting.h"
#include "MySpaceShip.h"
#include "MyBullet.h"
#include "Weapon.h"
#include "WeaponManager.h"
#include "EnemyManager.h"
#include "CollisionDetect.h"
namespace jm
{
	class MainCombined : public Game2D
	{
	public:
		MySpaceShip spaceship;
		EnemyManager enemymanager;
		MyBullet* bullet1 = nullptr;
		MyBullet* bullet2 = nullptr;
		WeaponManager weaponmanager; // 총알 관리자
		float timer; // 총알 타이머

	public:
		MainCombined():timer(0){
			enemymanager.createSmallUFO(1);
		}

		~MainCombined()
		{
			if (bullet1 != nullptr) {
				delete bullet1;
				delete bullet2;
			}
		}

		void update() override
		{
			
			// 우주선움직임
			if (isKeyPressed(GLFW_KEY_A)) spaceship.update(GLFW_KEY_A, getTimeStep());
			if (isKeyPressed(GLFW_KEY_D)) spaceship.update(GLFW_KEY_D, getTimeStep());
			if (isKeyPressed(GLFW_KEY_W)) spaceship.update(GLFW_KEY_W, getTimeStep());
			if (isKeyPressed(GLFW_KEY_S)) spaceship.update(GLFW_KEY_S, getTimeStep());
			spaceship.direction = getCursorPos();

			// 총알생성
			if (this->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			{
				//총알타이머
				timer += getTimeStep();
				//총알타이머 딜레이 도달시
				if (timer >= weaponmanager.getDelay() * getTimeStep()) {
					//첫번쨰 무기에서 나가는 총알 생성
					weaponmanager.createBullet(spaceship, getCursorPos(), 0.25);
					timer = 0; // 타이머 초기화
				}
			}
			weaponmanager.update(getTimeStep()); //총알이동
			weaponmanager.draw(); //총알 rendering
			
			srand(static_cast<size_t>(time(NULL)));
			
			enemymanager.update(getTimeStep(), spaceship.center); //적유닛 이동
			enemymanager.draw(); //적유닛 rendering

			CollisionDetect::detectCollision_bullet_enemy(enemymanager, weaponmanager);

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

			endTransformation();

			// 불필요한 총알 삭제
			weaponmanager.deleteBullet();
		}

	};
}