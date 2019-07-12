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
#include "Timer.h"
#include "Stage.h"
#include "ScoreBoard.h"
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
		float timer_bullet; // 총알 타이머
		CollisionDetect collisionDetect;
		Stage stage;
		Timer timer;

		ScoreBoard scoreboard;
		int temp_score; //점수 임시변수
		int temp_damage; //데미지 임시변수
		

	public:
		MainCombined() :timer_bullet(0), temp_score(0){
			timer.start();
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
				timer_bullet += getTimeStep();
				//총알타이머 딜레이 도달시
				if (timer_bullet >= weaponmanager.getDelay() * getTimeStep()) {
					//첫번쨰 무기에서 나가는 총알 생성
					weaponmanager.createBullet(spaceship, getCursorPos(), 0.25);
					timer_bullet = 0; // 타이머 초기화
				}
			}
			weaponmanager.update(getTimeStep()); //총알이동
			weaponmanager.draw(); //총알 rendering

			srand(static_cast<size_t>(time(NULL)));

			stage.createEnemy(enemymanager,timer); //스테이지 별 적유닛생성
			enemymanager.update(getTimeStep(), spaceship.center); //적유닛 이동
			enemymanager.draw(); //적유닛 rendering

			temp_score = collisionDetect.detectCollision_bullet_enemy(enemymanager, weaponmanager); // 적유닛-총알 충돌 탐지시 적,총알 객체 제거 및 점수반환 
			scoreboard.addScore(temp_score);

			temp_damage = collisionDetect.detectCollision_unit_enemy(enemymanager, spaceship); //적유닛-사용자유닛 충돌 탐지시 사용자유닛 체력 감소
			if (temp_damage != 0) {
				scoreboard.minusPlayerHp(temp_damage); 
			}

			weaponmanager.deleteBullet(); // 필요없는 총알 제거

			if (temp_score != 0 || temp_damage != 0) {
				scoreboard.draw();
				temp_score = 0;
				temp_damage = 0;
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
		}

	};
}