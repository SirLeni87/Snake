#include "Menu.h"

#include <filesystem>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(1,1), "The Eel", Style::None);

	ResourceHolder::insertFont("lumberjack", "resources/fonts/Lumberjack.otf");
	ResourceHolder::insertFont("roboto-thin", "resources/fonts/Roboto-Thin.ttf");
	ResourceHolder::insertFont("roboto-regular", "resources/fonts/Roboto-Regular.ttf");
	ResourceHolder::insertTexture("menu", "resources/images/menu.png");
	ResourceHolder::insertTexture("background", "resources/images/background-water.png");
	ResourceHolder::insertTexture("background-info", "resources/images/background-modifiers.png");
	ResourceHolder::insertTexture("algae-up", "resources/images/algae-up.png");
	ResourceHolder::insertTexture("algae-left", "resources/images/algae-left.png");
	ResourceHolder::insertTexture("algae-right", "resources/images/algae-right.png");
	ResourceHolder::insertTexture("algae-down", "resources/images/algae-down.png");
	ResourceHolder::insertTexture("algae-corner", "resources/images/algae-corner.png");
	ResourceHolder::insertTexture("head", "resources/images/head.png");
	ResourceHolder::insertTexture("segment", "resources/images/segment.png");
	ResourceHolder::insertTexture("bent-segment", "resources/images/bent-segment.png");
	ResourceHolder::insertTexture("tail", "resources/images/tail.png");
	ResourceHolder::insertTexture("bent-tail", "resources/images/tail-bent1.png");
	ResourceHolder::insertTexture("bent-tail2", "resources/images/tail-bent2.png");
	ResourceHolder::insertTexture("head2", "resources/images/head2.png");
	ResourceHolder::insertTexture("segment2", "resources/images/segment2.png");
	ResourceHolder::insertTexture("bent-segment2", "resources/images/bent-segment2.png");
	ResourceHolder::insertTexture("tail2", "resources/images/tail2.png");
	ResourceHolder::insertTexture("bent-tail3", "resources/images/tail-bent3.png");
	ResourceHolder::insertTexture("bent-tail4", "resources/images/tail-bent4.png");
	ResourceHolder::insertTexture("fish1", "resources/images/fish1.png");
	ResourceHolder::insertTexture("fish2", "resources/images/fish2.png");
	ResourceHolder::insertTexture("nautilus", "resources/images/nautilus.png");
	ResourceHolder::insertTexture("shrimp", "resources/images/shrimp.png");
	ResourceHolder::insertTexture("pufferfish", "resources/images/pufferfish.png");
	ResourceHolder::insertTexture("jellyfish", "resources/images/jellyfish.png");
	ResourceHolder::insertTexture("whirlpool", "resources/images/whirlpool.png");
	ResourceHolder::insertTexture("net", "resources/images/net.png");
	ResourceHolder::insertTexture("sailfish", "resources/images/sailfish.png");
	ResourceHolder::insertTexture("crab", "resources/images/crab.png");
	ResourceHolder::insertTexture("indicator", "resources/images/crab_indicator.png");
	ResourceHolder::insertTexture("shell", "resources/images/shell.png");

	window.close();

	Menu menu;
	menu.menu();

	return 0;
}