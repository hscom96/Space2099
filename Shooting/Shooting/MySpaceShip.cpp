#include "MySpaceShip.h"

namespace jm {
	void MySpaceShip::draw()
	{
		beginTransformation();
		translate(center);
		drawFilledBox(Colors::orange, 0.15f, 0.12f); // body
		translate(0.03, 0.06f);
		drawFilledBox(Colors::green, 0.25f, 0.02f); //shooter
		translate(0, -0.12f);
		drawFilledBox(Colors::green, 0.25f, 0.02f); //shooter2
		translate(0.07f, 0.06f);
		rotate(270.0f);
		drawFilledTriangle(Colors::darkRed, 0.095f); // head
		endTransformation();
	}

	void MySpaceShip:: update() {
		if (abs(center.x) <= framesize_X / 2 && abs(center.y) <= framesize_Y / 2) {

		}
	}
}