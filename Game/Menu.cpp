#include "Menu.h"


GameObject* createPlay()
{
	GameObject* Play = new GameObject({ 100,100 });
	Text* txt = new Text("Play", 100, White, "PressStart2P-Regular.ttf");
	Play->AddComponent(txt);
	return Play;
}

GameObject* createResume()
{
	GameObject* Resume = new GameObject({ 100,100 });
	Text* txt = new Text("Resume", 100, White, "PressStart2P-Regular.ttf");
	Resume->AddComponent(txt);
	return Resume;
}


GameObject* createQuit()
{
	GameObject* Quit = new GameObject({ 100,400 });
	Text* txt = new Text("Quit", 100, White, "PressStart2P-Regular.ttf");
	Quit->AddComponent(txt);
	return Quit;
}

GameObject* createRetry()
{
	GameObject* Play = new GameObject({ 100,100 });
	Text* txt = new Text("Retry", 100, White, "PressStart2P-Regular.ttf");
	Play->AddComponent(txt);
	return Play;
}