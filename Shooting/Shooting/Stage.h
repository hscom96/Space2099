#include "EnemyManager.h"
#include <iostream>
#include "Timer.h"

namespace jm {
	class Stage {
	private :
		double delay_smallUFO;
		double delay_bigUFO;
		double delay_boss;
		double lastTime_smallUFO;
		double lastTime_bigUFO;
		double lastTime_boss;
		double currentTime;
		
	public:
		Stage() :delay_smallUFO(3000), delay_bigUFO(9000), delay_boss(30000) {
			lastTime_smallUFO = 0;
			lastTime_bigUFO = 0;
			lastTime_boss = 0;
		}
		void createEnemy(EnemyManager& enemyManager, Timer& timer) {
			currentTime = timer.stopAndGetElapsedMilli();
			if (currentTime - lastTime_smallUFO >= delay_smallUFO) {
				enemyManager.createSmallUFO(2);
				lastTime_smallUFO = currentTime;
			}
			if (currentTime - lastTime_bigUFO >= delay_bigUFO) {
				enemyManager.createBigUFO(1);
				lastTime_bigUFO = currentTime;
			}
			if (currentTime-lastTime_boss >= delay_boss) {
				enemyManager.createBoss(1);
				lastTime_boss = currentTime;
			}
		}
	};
}