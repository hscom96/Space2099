#pragma once
#include "Enemy.h"
#include "SmallUFO.h"
#include "MySpaceShip.h"
namespace jm {
	class EnemyManager {
	private:
		std::vector<Enemy*> Enemy_Container; // ���� ��� �����̳�
		std::vector<Enemy*>::iterator it; //�����̳� �ݺ���
		Enemy* enemy = nullptr;
	public:
		//num���� SmallUFO ����
		void createSmallUFO(int num) {
			for (int i = 0; i < num; i++) {
				enemy = new SmallUFO();
				Enemy_Container.push_back(enemy);
			}
		}

		//�����̳� ���� Enemy �̵�
		void update(const float& dt, vec2 direction) {
			for (it = Enemy_Container.begin(); it != Enemy_Container.end(); it++) {
				(*it)->update(dt, direction);
			}
		}

		void draw() {
			for (it = Enemy_Container.begin(); it != Enemy_Container.end(); it++) {
				(*it)->draw();
			}
		}

	};
}