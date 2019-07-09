#pragma once
#include "Game2D.h"
#include "MyBullet.h"
#include "Weapon.h"

namespace jm {
	class WeaponManager {
	private:
		std::vector<Weapon*> bullet_Container; // �Ѿ��� ��� �����̳�
		int delay;
		MyBullet* bullet = nullptr;
		std::vector<Weapon*>::iterator it; //�Ѿ� �����̳� �ݺ���

	public:
		WeaponManager() : delay(75.0f) {}

		int getDelay() {
			return delay;
		}

		void setDelay(int delay) {
			if (0.0f < delay) {
				this->delay = delay;
			}
		}

		void createBullet(const MySpaceShip& spaceship, vec2 direction, float velocity) {
			bullet = new MyBullet;
			bullet->center = spaceship.center;
			bullet->center.y += 0.08f;
			bullet->velocity = vec2(velocity, velocity);
			bullet->direction = direction;
			bullet->setAngle(GetDirectionAngle(bullet->center, bullet->direction));
			bullet_Container.push_back(bullet);
		}


		//���ʿ����Ѿ� ����
		void deleteBullet() {
			for (it = bullet_Container.begin(); it != bullet_Container.end();) {
				Weapon* temp = *it;   // �ӽú���
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

		//�����̳� �� ����Ѿ� �̵�
		void update(const float& dt) {
			if (bullet_Container.empty() != true) {
				for (it = bullet_Container.begin(); it != bullet_Container.end(); it++) {
					(*it)->update(dt);
				}
			}

		}

		void draw() {
			if (bullet_Container.empty() != true) {
				beginTransformation();
				{
					for (it = bullet_Container.begin(); it != bullet_Container.end(); it++) 
					{
						(*it)->draw();
					}
				}
				endTransformation();
			}
		}
	};
}