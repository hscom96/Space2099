#include "Game2D.h"
#include "MainCombined.h"

namespace jm
{
	class MouseExample : public Game2D
	{
	public:
		void update() override
		{
			const vec2 mouse_pos = getCursorPos();

			if (this->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1) == true)
			{
				translate(mouse_pos);
				drawFilledCircle(Colors::gold, 0.1f);
			}

			if (this->isMouseButtonPressed(GLFW_MOUSE_BUTTON_2) == true)
			{
				translate(mouse_pos);
				drawFilledCircle(Colors::red, 0.1f);
			}
		}
	};
}

int main(void)
{
	jm::MainCombined().init("Space 2099", 1024, 768, false).run();
	return 0;
}
