#include "Game2D.h"
#include "enemy.h"
#include "Weapon.h"
#include "EnemyManager.h"
#include "WeaponManager.h"
#include <iostream>
#include "Timer.h"
#define noDamageTime 1000

namespace jm {
	class CollisionDetect {
	private:
		Timer timer;
		double currentTime;
		double lastTime;
		bool collisionFlag;

	public:
		CollisionDetect() :collisionFlag(true) {}
		//총알-적유닛 충돌체크
		template<class T1, class T2>
		bool isCollision_Circle(T1 circle1, T2 circle2) {
			if (GetDirectionLength(circle1.getCenter(), circle2.getCenter()) < circle1.getRadius() + circle2.getRadius()) {
				return true;
			}
			else {
				return false;
			}
		}

		//총알-적유닛 충돌감지 
		//반환값 : 적 점수
		int detectCollision_bullet_enemy(EnemyManager& enemyContainer, WeaponManager& weaponContainer) {
			std::vector<Enemy*>::iterator it_enemy;
			std::vector<Weapon*>::iterator it_weapon;
			bool isErase;
			int score = 0;

			for (it_enemy = enemyContainer.getContainer().begin(); it_enemy != enemyContainer.getContainer().end();) {
				Enemy* temp_enemy = *it_enemy;   // 임시변수
				isErase = false;
				if (weaponContainer.getContainer().size() == 0) break; // 컨테이너사이즈가 0이면 더 돌필요없이 종료
				for (it_weapon = weaponContainer.getContainer().begin(); it_weapon != weaponContainer.getContainer().end();it_weapon++) {
					Weapon* temp_weapon = *it_weapon;   // 임시변수
					if (isCollision_Circle<Weapon, Enemy>(*(temp_weapon), *(temp_enemy))) {//충돌 발생
						temp_enemy->minusHp(temp_weapon->getDamage());//공격처리(유닛체력감소)
						if (temp_enemy->getHp() <= 0) { //유닛의 Hp가 0 이하이면
							score = temp_enemy->getScore(); // 적유닛 점수 반환
							if (temp_enemy != nullptr)  // 적유닛  메모리해제하기.
								delete temp_enemy;
							temp_enemy = nullptr;
							it_enemy = enemyContainer.getContainer().erase(it_enemy);
							isErase = true;
							return score;
						}
						if (temp_weapon != nullptr)  // 총알 메모리해제하기.
							delete temp_weapon;
						temp_weapon = nullptr;
						weaponContainer.getContainer().erase(it_weapon);
						break;
					}
				}
				if (isErase == false) it_enemy++;
			}
			return score;
		}

		//사용자유닛-적유닛 충돌감지 (충돌후 일시적 무적상태)
		//반환값 : 사용자 데미지
		int detectCollision_unit_enemy(EnemyManager& enemyContainer, MySpaceShip& mySpaceShip) {
			currentTime = timer.stopAndGetElapsedMilli();
			
			std::vector<Enemy*>::iterator it;
			for (it = enemyContainer.getContainer().begin(); it != enemyContainer.getContainer().end();it++) {
				if (isCollision_Circle<Enemy, MySpaceShip>((**it), mySpaceShip)) {
					if (currentTime > noDamageTime || collisionFlag) {
						collisionFlag = 0;
						timer.start();
						return (*it)->getDamage();
						
					}
				}
			}
		
			return 0;
		}
	};
}