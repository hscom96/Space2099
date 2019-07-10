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
		bool isCollision_bullet_enemy(Weapon* weapon, Enemy* enemy) {
			if (GetDirectionLength(enemy->getCenter(), weapon->getCenter()) < enemy->getRadius() + weapon->getRadius()) {
				return true;
			}
			else {
				return false;
			}
		}

		//�Ѿ�-������ �浹����
		void detectCollision_bullet_enemy(EnemyManager& enemyContainer, WeaponManager& weaponContainer) {
			std::vector<Enemy*>::iterator it_enemy;
			std::vector<Weapon*>::iterator it_weapon;
			bool isErase;

			for (it_enemy = enemyContainer.getContainer().begin(); it_enemy != enemyContainer.getContainer().end();) {
				Enemy* temp_enemy = *it_enemy;   // �ӽú���
				isErase = false;
				for (it_weapon = weaponContainer.getContainer().begin(); it_weapon != weaponContainer.getContainer().end();it_weapon++) {
					Weapon* temp_weapon = *it_weapon;   // �ӽú���
					if (isCollision_bullet_enemy(*(it_weapon), *(it_enemy))) {//�浹 �߻�
						temp_enemy->minusHp(temp_weapon->getDamage());//����ó��(����ü�°���)
						if (temp_enemy->getHp() <= 0) { //������ Hp�� 0 �����̸�
							if (temp_enemy != nullptr)  // ������  �޸������ϱ�.
								delete temp_enemy;
							temp_enemy = nullptr;
							it_enemy = enemyContainer.getContainer().erase(it_enemy);
							isErase = true;
						}
						if (temp_weapon != nullptr)  // �Ѿ� �޸������ϱ�.
							delete temp_weapon;
						temp_weapon = nullptr;
						weaponContainer.getContainer().erase(it_weapon);
						break;
					}
				}
				if (enemyContainer.getContainer().size() == 0)  // �����̳ʻ���� 0�̸� �� ���ʿ���� ����
					break;
				if (isErase == false) it_enemy++;
			}
		}


	};
}