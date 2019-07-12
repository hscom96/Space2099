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
		int playerHp;
		float elaspeTime;
	public:
		ScoreBoard() :score(0), playerHp(5), elaspeTime(0) {}

		void addScore(int score) {
			this->score += score;
		}
		int getScore() {
			return score;
		}

		void minusPlayerHp(int player_hp) {
			this->playerHp -= player_hp;
		}
		int getPlayerhp() {
			return playerHp;
		}

		void draw() {
			system("cls");
			std::cout << "스코어 : "<< score << std::endl;
			std::cout << "체력 : "<< playerHp << std::endl;
		}

	};
}
