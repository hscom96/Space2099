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
		WeaponManager weaponmanager; // �Ѿ� ������
		float timer_bullet; // �Ѿ� Ÿ�̸�
		CollisionDetect collisionDetect;
		Stage stage;
		Timer timer;

		ScoreBoard scoreboard;
		int temp_score; //���� �ӽú���
		int temp_damage; //������ �ӽú���
		

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
			// ���ּ�������
			if (isKeyPressed(GLFW_KEY_A)) spaceship.update(GLFW_KEY_A, getTimeStep());
			if (isKeyPressed(GLFW_KEY_D)) spaceship.update(GLFW_KEY_D, getTimeStep());
			if (isKeyPressed(GLFW_KEY_W)) spaceship.update(GLFW_KEY_W, getTimeStep());
			if (isKeyPressed(GLFW_KEY_S)) spaceship.update(GLFW_KEY_S, getTimeStep());
			spaceship.direction = getCursorPos();

			// �Ѿ˻���
			if (this->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			{
				//�Ѿ�Ÿ�̸�
				timer_bullet += getTimeStep();
				//�Ѿ�Ÿ�̸� ������ ���޽�
				if (timer_bullet >= weaponmanager.getDelay() * getTimeStep()) {
					//ù���� ���⿡�� ������ �Ѿ� ����
					weaponmanager.createBullet(spaceship, getCursorPos(), 0.25);
					timer_bullet = 0; // Ÿ�̸� �ʱ�ȭ
				}
			}
			weaponmanager.update(getTimeStep()); //�Ѿ��̵�
			weaponmanager.draw(); //�Ѿ� rendering

			srand(static_cast<size_t>(time(NULL)));

			stage.createEnemy(enemymanager,timer); //�������� �� �����ֻ���
			enemymanager.update(getTimeStep(), spaceship.center); //������ �̵�
			enemymanager.draw(); //������ rendering

			temp_score = collisionDetect.detectCollision_bullet_enemy(enemymanager, weaponmanager); // ������-�Ѿ� �浹 Ž���� ��,�Ѿ� ��ü ���� �� ������ȯ 
			scoreboard.addScore(temp_score);

			temp_damage = collisionDetect.detectCollision_unit_enemy(enemymanager, spaceship); //������-��������� �浹 Ž���� ��������� ü�� ����
			if (temp_damage != 0) {
				scoreboard.minusPlayerHp(temp_damage); 
			}

			weaponmanager.deleteBullet(); // �ʿ���� �Ѿ� ����

			if (temp_score != 0 || temp_damage != 0) {
				scoreboard.draw();
				temp_score = 0;
				temp_damage = 0;
			}
			// ���콺 ������ rendering	
			beginTransformation();
			{
				translate(getCursorPos());
				setLineWidth(4.0f);
				drawWiredCircle(Colors::red, 0.07f);
				drawLine(Colors::red, vec2(-0.07f, 0), Colors::red, vec2(+0.07f, 0));
				drawLine(Colors::red, vec2(0, -0.07f), Colors::red, vec2(0, +0.07f));
			}
			endTransformation();

			//���ּ� rendering
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