#include "SinglePlayer.h"

using namespace sf;

SinglePlayer::SinglePlayer()
{
	RenderWindow window(VideoMode(1536, 512), "MySnake", Style::Titlebar | Style::Close);

	Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			}
		}
	}
}
