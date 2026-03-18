#include "Menu.h"


GameObject* createPlay()
{
	GameObject* Play = new GameObject(sf::Vector2f( 100,100 ));
	Text* txt = new Text("Play", 100, Red, "A Love of Thunder.ttf");
	Play->AddComponent(txt);
	return Play;
}

GameObject* createResume()
{
	GameObject* Resume = new GameObject(sf::Vector2f(100, 100));
	Text* txt = new Text("Resume", 100, Red, "A Love of Thunder.ttf");
	Resume->AddComponent(txt);
	return Resume;
}


GameObject* createQuit()
{
	GameObject* Quit = new GameObject(sf::Vector2f(100, 400));
	Text* txt = new Text("Quit", 100, Red, "A Love of Thunder.ttf");
	Quit->AddComponent(txt);
	return Quit;
}

GameObject* createRetry()
{
	GameObject* Play = new GameObject(sf::Vector2f(100, 100));
	Text* txt = new Text("Retry", 100, Red, "A Love of Thunder.ttf");
	Play->AddComponent(txt);
	return Play;
}