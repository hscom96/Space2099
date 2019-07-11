#include "Game2D.h"
#include "enemy.h"
#include "Weapon.h"
#include "EnemyManager.h"
#include "WeaponManager.h"
#include <iostream>
namespace jm {
	class CollisionDetect {
	private:
	public:
		//�Ѿ�-������ �浹üũ
		template<class T1, class T2>
		bool isCollision_Circle(T1 circle1, T2 circle2) {
			if (GetDirectionLength(circle1->getCenter(), circle2->getCenter()) < circle1->getRadius() + circle2->getRadius()) {
				return true;
			}
			else {
				return false;
			}
		}

		//�Ѿ�-������ �浹���� 
		//��ȯ�� : �� ����
		int detectCollision_bullet_enemy(EnemyManager& enemyContainer, WeaponManager& weaponContainer) {
			std::vector<Enemy*>::iterator it_enemy;
			std::vector<Weapon*>::iterator it_weapon;
			bool isErase;
			int score = 0;

			for (it_enemy = enemyContainer.getContainer().begin(); it_enemy != enemyContainer.getContainer().end();) {
				Enemy* temp_enemy = *it_enemy;   // �ӽú���
				isErase = false;
				if (weaponContainer.getContainer().size() == 0) break; // �����̳ʻ���� 0�̸� �� ���ʿ���� ����
				for (it_weapon = weaponContainer.getContainer().begin(); it_weapon != weaponContainer.getContainer().end();it_weapon++) {
					Weapon* temp_weapon = *it_weapon;   // �ӽú���
					if (isCollision_Circle<Weapon*, Enemy*>(*(it_weapon), *(it_enemy))) {//�浹 �߻�
						temp_enemy->minusHp(temp_weapon->getDamage());//����ó��(����ü�°���)
						if (temp_enemy->getHp() <= 0) { //������ Hp�� 0 �����̸�
							score = temp_enemy->getScore(); // ������ ���� ��ȯ
							if (temp_enemy != nullptr)  // ������  �޸������ϱ�.
								delete temp_enemy;
							temp_enemy = nullptr;
							it_enemy = enemyContainer.getContainer().erase(it_enemy);
							isErase = true;
							return score;
						}
						if (temp_weapon != nullptr)  // �Ѿ� �޸������ϱ�.
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

		//
	};
}