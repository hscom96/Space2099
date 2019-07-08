#pragma once
#include<iostream>
#include "Game2D.h"
#include "math.h"
#include "SmallUFO.h"
#include "Setting.h"
#include "MySpaceShip.h"
#include "MyBullet.h"

namespace jm
{
	class MainCombined : public Game2D
	{
	public:
		MySpaceShip spaceship;
		SmallUFO smallufo[10];

		MyBullet* bullet1 = nullptr;
		MyBullet* bullet2 = nullptr;
		std::vector<MyBullet*> bullet_Container; // �Ѿ��� ��� �����̳�
		float timer; // �Ѿ� Ÿ�̸�

	public:
		MainCombined():timer(0),spaceship(50.f){}

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
			if (isKeyPressed(GLFW_KEY_A))  spaceship.center.x -= 0.15f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_D))	spaceship.center.x += 0.15f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_W))	spaceship.center.y += 0.15f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_S))	spaceship.center.y -= 0.15f * getTimeStep();
			spaceship.direction = getCursorPos();

			// �Ѿ˻���
			if (this->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			{
				//�Ѿ�Ÿ�̸�
				timer += getTimeStep();
				//�Ѿ�Ÿ�̸� ������ ���޽�
				if (timer >= spaceship.getDelay() * getTimeStep()) {
					//ù���� ���⿡�� ������ �Ѿ� ����
					bullet1 = new MyBullet;
					bullet1->center = spaceship.center;
					bullet1->center.y += 0.08f;
					bullet1->velocity = vec2(0.20f, 0.20f);
					bullet1->direction = getCursorPos();
					bullet1->setAngle( GetDirectionAngle(bullet1->center, bullet1->direction) );
					bullet_Container.push_back(bullet1);

					//�ι��� ���⿡�� ������ �Ѿ� ����
					bullet2 = new MyBullet;
					bullet2->center = spaceship.center;
					bullet2->center.y -= 0.08f;
					bullet2->velocity = vec2(0.20f, 0.20f);
					bullet2->direction = getCursorPos();
					bullet2->setAngle(GetDirectionAngle(bullet1->center, bullet1->direction));
					bullet_Container.push_back(bullet2);

					timer = 0; // Ÿ�̸� �ʱ�ȭ
				}
			}

			std::vector<MyBullet*>::iterator it; //�Ѿ� �����̳� �ݺ���
			//�Ѿ��̵�
			if (bullet_Container.empty() != true) {
				for (it = bullet_Container.begin(); it != bullet_Container.end(); it++) {
					(*it)->update(getTimeStep());
				}
			}

			//�Ѿ� rendering
			if (bullet_Container.empty() != true) {
				beginTransformation();
				{
					for (it = bullet_Container.begin(); it != bullet_Container.end(); it++) {
						(*it)->draw();
					}
				}
				endTransformation();
			}

			srand(static_cast<size_t>(time(NULL)));
			//���� UFO �̵�
			for (int i = 0; i < 10; i++) {
				smallufo[i].update(getTimeStep(),spaceship.center);
			}
			//���� UFO rendering
			beginTransformation();
			{
				for (int i = 0; i < 10; i++) {
					smallufo[i].draw();
				}
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

			endTransformation();

			// ���ʿ��� �Ѿ� ����
			if (bullet_Container.size() >= 14) {
				MyBullet::deleteBullet(bullet_Container);
			}
		}

	};
}