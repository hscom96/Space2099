#include "Game2D.h"
#include "MainCombined.h"

int main(void)
{
	jm::MainCombined().init("Space 2099", 1024, 768, false).run();
	return 0;
}
