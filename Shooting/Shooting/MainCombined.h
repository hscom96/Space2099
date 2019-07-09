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
		WeaponManager weaponmanager; // �Ѿ� ������
		float timer; // �Ѿ� Ÿ�̸�

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
				timer += getTimeStep();
				//�Ѿ�Ÿ�̸� ������ ���޽�
				if (timer >= weaponmanager.getDelay() * getTimeStep()) {
					//ù���� ���⿡�� ������ �Ѿ� ����
					weaponmanager.createBullet(spaceship, getCursorPos(), 0.25);
					timer = 0; // Ÿ�̸� �ʱ�ȭ
				}
			}
			weaponmanager.update(getTimeStep()); //�Ѿ��̵�
			weaponmanager.draw(); //�Ѿ� rendering
			
			srand(static_cast<size_t>(time(NULL)));
			
			enemymanager.update(getTimeStep(), spaceship.center); //������ �̵�
			enemymanager.draw(); //������ rendering

			CollisionDetect::detectCollision_bullet_enemy(enemymanager, weaponmanager);

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

			endTransformation();

			// ���ʿ��� �Ѿ� ����
			weaponmanager.deleteBullet();
		}

	};
}