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


	};
}
