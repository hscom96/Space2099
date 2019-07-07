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
		vec2 direction = vec2(1.0f, 0.0f); //ȸ��


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

		//���ʿ����Ѿ� ����
		static void deleteBullet(std::vector<MyBullet*>& bullet_Container) {
			std::vector<MyBullet*>::iterator it; //�Ѿ� �����̳� �ݺ���
			for (it = bullet_Container.begin(); it != bullet_Container.end();) {
				MyBullet* temp = *it;   // �ӽú���
				if (abs(temp->center.x) > framesize_X || abs(temp->center.y) > framesize_Y)
				{
					if (temp != nullptr)  // nullptr�˻��� �޸������ϱ�.
						delete temp;
					temp = nullptr;
					it = bullet_Container.erase(it);
					if (bullet_Container.size() == 0)  // �����̳ʻ���� 0�̸� �� ���ʿ���� ����
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
		std::vector<MyBullet*> bullet_Container; // �Ѿ��� ��� �����̳�
		float timer; // �Ѿ� Ÿ�̸�
		float delay; //�Ѿ� ������


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
				//�Ѿ�Ÿ�̸� �����̵��޽�
				if (timer >= delay * getTimeStep()) {
					//ù���� ���⿡�� ������ �Ѿ� ����
					bullet1 = new MyBullet;
					bullet1->center = spaceship.center;
					bullet1->center.y += 0.08f;
					bullet1->velocity = vec2(0.20f, 0.20f);
					bullet1->direction = getCursorPos();
					bullet1->angle = GetDirectionAngle(bullet1->center, bullet1->direction);
					bullet_Container.push_back(bullet1);

					//�ι��� ���⿡�� ������ �Ѿ� ����
					bullet2 = new MyBullet;
					bullet2->center = spaceship.center;
					bullet2->center.y -= 0.08f;
					bullet2->velocity = vec2(0.20f, 0.20f);
					bullet2->direction = getCursorPos();
					bullet2->angle = GetDirectionAngle(bullet2->center, bullet2->direction);
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

			//���� UFO rendering
			beginTransformation();
			{
				srand(static_cast<size_t>(time(NULL)));
				for (int i = 0; i < 40; i++) {
					smallufo[i].draw();
				}
			}
			endTransformation();

			// ���ʿ��� �Ѿ� ����
			if (bullet_Container.size() >= 14) {
				MyBullet::deleteBullet(bullet_Container);
			}
		}

	};
}