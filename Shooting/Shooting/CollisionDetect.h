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
		static bool isCollision_bullet_enemy(Weapon* weapon, Enemy* enemy) {
			if (GetDirectionLength(enemy->getCenter(), weapon->getCenter()) < enemy->getRadius() + weapon->getRadius()) {
				return true;
			}
			else {
				return false;
			}
		}

		//총알-적유닛 충돌감지
		static void detectCollision_bullet_enemy(EnemyManager& enemyContainer, WeaponManager& weaponContainer) {
			std::vector<Enemy*>::iterator it_enemy;
			std::vector<Weapon*>::iterator it_weapon;

			for (it_enemy = enemyContainer.getContainer().begin(); it_enemy != enemyContainer.getContainer().end();it_enemy++) {
				Enemy* temp_enemy = *it_enemy;   // 임시변수
				for (it_weapon = weaponContainer.getContainer().begin(); it_weapon != weaponContainer.getContainer().end();) {
					Weapon* temp_weapon = *it_weapon;   // 임시변수
					if (isCollision_bullet_enemy(*(it_weapon), *(it_enemy))) {//충돌 발생
						temp_enemy->minusHp(temp_weapon->getDamage());//공격처리(유닛체력감소)
						//if (temp_enemy->getHp() <= 0) { //유닛의 Hp가 0 이하이면
						//	if (temp_enemy != nullptr)  // nullptr검사후 메모리해제하기.
						//		delete temp_enemy;
						//	temp_enemy = nullptr;
						//	it_enemy = enemyContainer.getContainer().erase(it_enemy);
						//}
							if (temp_weapon != nullptr)  // nullptr검사후 메모리해제하기.
								delete temp_weapon;
							temp_weapon = nullptr;
							it_weapon = weaponContainer.getContainer().erase(it_weapon);
						
					}
					else { //충돌 미발생
						//it_enemy++;
						it_weapon++;
					}
				}
			}
		}
	};
}