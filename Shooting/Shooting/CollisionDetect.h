#include "Game2D.h"
#include "enemy.h"
#include "Weapon.h"
#include "EnemyManager.h"
#include "WeaponManager.h"

namespace jm {
	class CollisionDetect {
	private:
	public:
		//�Ѿ�-������ �浹üũ
		static bool isCollision_bullet_enemy(Weapon* weapon, Enemy* enemy) {
			if (GetDirectionLength(enemy->getCenter(), weapon->getCenter()) < enemy->getRadius() + weapon->getRadius()) {
				return true;
			}
			else {
				return false;
			}
		}

		//�Ѿ�-������ �浹����
		static void detectCollision_bullet_enemy(EnemyManager& enemyContainer, WeaponManager& weaponContainer) {
			std::vector<Enemy*>::iterator it_enemy;
			std::vector<Weapon*>::iterator it_weapon;

			for (it_enemy = enemyContainer.getContainer().begin(); it_enemy != enemyContainer.getContainer().end();it_enemy++) {
				Enemy* temp_enemy = *it_enemy;   // �ӽú���
				for (it_weapon = weaponContainer.getContainer().begin(); it_weapon != weaponContainer.getContainer().end();) {
					Weapon* temp_weapon = *it_weapon;   // �ӽú���
					if (isCollision_bullet_enemy(*(it_weapon), *(it_enemy))) {//�浹 �߻�
						temp_enemy->minusHp(temp_weapon->getDamage());//����ó��(����ü�°���)
						//if (temp_enemy->getHp() <= 0) { //������ Hp�� 0 �����̸�
						//	if (temp_enemy != nullptr)  // nullptr�˻��� �޸������ϱ�.
						//		delete temp_enemy;
						//	temp_enemy = nullptr;
						//	it_enemy = enemyContainer.getContainer().erase(it_enemy);
						//}
							if (temp_weapon != nullptr)  // nullptr�˻��� �޸������ϱ�.
								delete temp_weapon;
							temp_weapon = nullptr;
							it_weapon = weaponContainer.getContainer().erase(it_weapon);
						
					}
					else { //�浹 �̹߻�
						//it_enemy++;
						it_weapon++;
					}
				}
			}
		}
	};
}