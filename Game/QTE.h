#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Scene;
class GameObject;
class Text;
class ArrowMiniGame 
{
public:
    ArrowMiniGame(int ArrowNumber);

    void update(Scene* lvl);
    bool isFinished() const;
    bool playerWon() const;
	
    GameObject* getText() { return text; }
    GameObject* getTimerObj() { return timerObj; }
    void clearPtrs() { text = nullptr; timerObj = nullptr; }
    void hide(Scene* lvl);
    
private:
    std::vector<GameObject*> arrowObjects;
    int sequenceLength;
    std::vector<sf::Keyboard::Key> sequence;  // séquence de touches
    size_t currentIndex = 0;                   // où on en est dans la séquence
    float remainingTime;
    bool won = false;
    bool finished = false;
    sf::Clock clock;
    sf::Font font;
    sf::Font font2;
    sf::Keyboard::Key lastKeyPressed = sf::Keyboard::Key::Unknown;
    GameObject* text = nullptr;
    GameObject* timerObj = nullptr;
    
     float windowWidth = 800.f;
     float windowHeight = 800.f;

    void generateSequence(unsigned int length);
    void drawSequence(Scene* lvl);
};
