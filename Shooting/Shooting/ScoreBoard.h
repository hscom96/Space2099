#pragma once
#include "Enemy.h"
#include "Weapon.h"
#include "Game2D.h"
#include "Setting.h"
#include <stdlib.h>
#include <iostream>
namespace jm {
	class ScoreBoard
	{
	private:
		int score;
		int player_hp;
		float elaspe_time;
	public:
		ScoreBoard() :score(0), player_hp(5), elaspe_time(0) {}

		void addScore(int score) {
			this->score += score;
		}
		int getScore() {
			return score;
		}

		void setPlayer_hp(int player_hp) {
			this->player_hp = player_hp;
		}
		int getPlayer_hp() {
			return player_hp;
		}

		void draw() {
			system("cls");
			std::cout << "스코어 : "<< score << std::endl;
			std::cout << "체력 : "<< player_hp << std::endl;
		}

	};
}
