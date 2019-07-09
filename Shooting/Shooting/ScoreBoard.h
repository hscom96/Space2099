#pragma once
#include "Enemy.h"
#include "Weapon.h"
#include "Game2D.h"
#include "Setting.h"

namespace jm {
	class ScoreBoard
	{
	private:
		int score;
		int player_hp;
		float elaspe_time;
	public:
		ScoreBoard() :score(0), player_hp(5), elaspe_time(0) {}

		bool isCollision(Weapon & weapon, Enemy& enemy) {
			float length = GetDirectionLength(weapon.center, enemy.getCenter()); //���߽� �����ǰŸ�
			if (length < weapon.getRadius() + enemy.getRadius()) {
				int hp = enemy.getHp() - weapon.getDamage();
				if (hp <= 0) {
					score += enemy.getScore(); //��������
					return true;
				}
				else {
					enemy.setHp(hp);
					return false;
				}

			}
		}
	};
}
