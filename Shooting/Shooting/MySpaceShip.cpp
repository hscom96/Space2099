#include "MySpaceShip.h"

namespace jm {
	void MySpaceShip::draw()
	{
		beginTransformation();
		translate(center);
		drawFilledCircle(Colors::pink, radius); // body
		translate(0.02f, 0.07f);
		drawFilledBox(Colors::green, 0.12f, 0.02f); //shooter
		translate(0, -0.14f);
		drawFilledBox(Colors::green, 0.12f, 0.02f); //shooter2
		endTransformation();
	}

}