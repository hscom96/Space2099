#pragma once
#include "Game2D.h"
#include "MyBullet.h"
#include "Weapon.h"

namespace jm {
	class WeaponManager {
	private:
		std::vector<Weapon*> bullet_Container; // 총알을 담는 컨테이너
		int delay;
		MyBullet* bullet = nullptr;
		std::vector<Weapon*>::iterator it; //총알 컨테이너 반복자

	public:
		WeaponManager() : delay(75.0f) {}

		int getDelay() {
			return delay;
		}

		void setDelay(int delay) {
			if (0.0f < delay) {
				this->delay = delay;
			}
		}

		std::vector<Weapon*>& getContainer() {
			return bullet_Container;
		}

		void createBullet(const MySpaceShip& spaceship, vec2 direction, float velocity) {
			bullet = new MyBullet;
			bullet->setCenter(spaceship.center);
			bullet->setVelocity(vec2(velocity, velocity));
			bullet->setDirection(direction);
			bullet->setAngle(GetDirectionAngle(bullet->getCenter(), bullet->getDirection()));
			bullet_Container.push_back(bullet);
		}


		//맵범위 벗어난 총알 삭제
		void deleteBullet() {
			for (it = bullet_Container.begin(); it != bullet_Container.end();) {
				Weapon* temp = *it;   // 임시변수
				if (abs(temp->getCenter().x) > framesize_X || abs(temp->getCenter().y) > framesize_Y)
				{
					if (temp != nullptr)  // nullptr검사후 메모리해제하기.
						delete temp;
					temp = nullptr;
					it = bullet_Container.erase(it);
					if (bullet_Container.size() == 0)  // 컨테이너사이즈가 0이면 더 돌필요없이 종료
						break;
				}
				else {
					it++;
				}
			}
			}

		//컨테이너 안 모든총알 이동
		void update(const float& dt) {
			if (bullet_Container.empty() != true) {
				for (it = bullet_Container.begin(); it != bullet_Container.end(); it++) {
					(*it)->update(dt);
				}
			}

		}

		void draw() {
			if (bullet_Container.empty() != true) {
				beginTransformation();
				{
					for (it = bullet_Container.begin(); it != bullet_Container.end(); it++) 
					{
						(*it)->draw();
					}
				}
				endTransformation();
			}
		}
	};
}