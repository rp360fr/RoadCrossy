#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ArrowMiniGame 
{
public:
    ArrowMiniGame();

    void update(sf::RenderWindow& window);
    bool isFinished() const;
    bool playerWon() const;

private:
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

     float windowWidth = 800.f;
     float windowHeight = 800.f;

    void generateSequence(unsigned int length);
    void drawSequence(sf::RenderWindow& window);
};
