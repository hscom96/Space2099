#include "Game2D.h"
#include "enemy.h"
#include "Weapon.h"
#include "EnemyManager.h"
#include "WeaponManager.h"

namespace jm {
	class CollisionDetect {
	private:
	public:
		//총알-적유닛 충돌체크
		bool isCollision_bullet_enemy(Weapon* weapon, Enemy* enemy) {
			if (GetDirectionLength(enemy->getCenter(), weapon->getCenter()) < enemy->getRadius() + weapon->getRadius()) {
				return true;
			}
			else {
				return false;
			}
		}

		//총알-적유닛 충돌감지
		void detectCollision_bullet_enemy(EnemyManager& enemyContainer, WeaponManager& weaponContainer) {
			std::vector<Enemy*>::iterator it_enemy;
			std::vector<Weapon*>::iterator it_weapon;
			bool isErase;

			for (it_enemy = enemyContainer.getContainer().begin(); it_enemy != enemyContainer.getContainer().end();) {
				Enemy* temp_enemy = *it_enemy;   // 임시변수
				isErase = false;
				for (it_weapon = weaponContainer.getContainer().begin(); it_weapon != weaponContainer.getContainer().end();it_weapon++) {
					Weapon* temp_weapon = *it_weapon;   // 임시변수
					if (isCollision_bullet_enemy(*(it_weapon), *(it_enemy))) {//충돌 발생
						temp_enemy->minusHp(temp_weapon->getDamage());//공격처리(유닛체력감소)
						if (temp_enemy->getHp() <= 0) { //유닛의 Hp가 0 이하이면
							if (temp_enemy != nullptr)  // 적유닛  메모리해제하기.
								delete temp_enemy;
							temp_enemy = nullptr;
							it_enemy = enemyContainer.getContainer().erase(it_enemy);
							isErase = true;
						}
						if (temp_weapon != nullptr)  // 총알 메모리해제하기.
							delete temp_weapon;
						temp_weapon = nullptr;
						weaponContainer.getContainer().erase(it_weapon);
						break;
					}
				}
				if (enemyContainer.getContainer().size() == 0)  // 컨테이너사이즈가 0이면 더 돌필요없이 종료
					break;
				if (isErase == false) it_enemy++;
			}
		}


	};
}