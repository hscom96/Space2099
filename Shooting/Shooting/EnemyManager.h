#pragma once
#include "Enemy.h"
#include "SmallUFO.h"
#include "MySpaceShip.h"
#include "Boss.h"
#include "BigUFO.h"

namespace jm {
	class EnemyManager {
	private:
		std::vector<Enemy*> Enemy_Container; // 적을 담는 컨테이너
		std::vector<Enemy*>::iterator it; //컨테이너 반복자
		Enemy* enemy = nullptr;
	public:
		//num개의 SmallUFO 생성
		void createSmallUFO(int num) {
			for (int i = 0; i < num; i++) {
				enemy = new SmallUFO();
				Enemy_Container.push_back(enemy);
			}
		}

		//num개의 BigUFO 생성
		void createBigUFO(int num) {
			for (int i = 0; i < num; i++) {
				enemy = new BigUFO();
				Enemy_Container.push_back(enemy);
			}
		}

		//num개의 Boss 생성
		void createBoss(int num) {
			for (int i = 0; i < num; i++) {
				enemy = new Boss();
				Enemy_Container.push_back(enemy);
			}
		}


		//컨테이너 안의 Enemy 이동
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

		std::vector<Enemy*>& getContainer() {
			return Enemy_Container;
		}

	};
}