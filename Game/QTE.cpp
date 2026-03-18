#include "QTE.h"
#include <iostream>



ArrowMiniGame::ArrowMiniGame()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    sequenceLength = 1;      // 20 flèches
    remainingTime = 5.f;     // 20 secondes
    finished = false;
    currentIndex = 0;
    won = false;
    windowWidth = 800.f;   // ou passe la window en paramètre
    windowHeight = 800.f;
    generateSequence(sequenceLength);

    if (!font.openFromFile("./Assets/ArrowSymbols.ttf"))
        std::cerr << "Impossible de charger la police !\n";
    if (!font2.openFromFile("./Assets/3270NerdFont-Regular.ttf"))
        std::cerr << "Impossible de charger la police !\n";

    clock.restart();
}

void ArrowMiniGame::generateSequence(unsigned int length)
{
    sequence.clear();
    for (unsigned int i = 0; i < length; ++i)
    {
        int r = rand() % 4;
        switch (r)
        {
        case 0: sequence.push_back(sf::Keyboard::Key::Up); break;
        case 1: sequence.push_back(sf::Keyboard::Key::Down); break;
        case 2: sequence.push_back(sf::Keyboard::Key::Left); break;
        case 3: sequence.push_back(sf::Keyboard::Key::Right); break;
        }
    }
    currentIndex = 0;
}

void ArrowMiniGame::drawSequence(sf::RenderWindow& window)
{
    std::cout << "QTE" << std::endl;
    const float startX = 10.f;
    const float y = windowHeight / 2.f - 20.f;
    const float spacing = 25.f;           // espacement entre flèches
    const float maxDisplay = windowWidth - 20.f;

    for (size_t i = 0; i < sequence.size(); ++i)
    {
        sf::Text text(font);
        text.setCharacterSize(20); // taille des fleches
        text.setFillColor(i < currentIndex ? sf::Color::Green : sf::Color::White); // vert pour flèches déjà faites

        std::string arrow;
        switch (sequence[i])
        {
        case sf::Keyboard::Key::Up: arrow = "D"; break;
        case sf::Keyboard::Key::Down: arrow = "B"; break;
        case sf::Keyboard::Key::Left: arrow = "C"; break;
        case sf::Keyboard::Key::Right: arrow = "A"; break;
        default: arrow = "?"; break;
        }

        text.setString(arrow);

        float posX = startX + i * spacing;
        if (posX > maxDisplay) posX = maxDisplay;
        text.setPosition({ posX, y });
        window.draw(text);
    }
}

void ArrowMiniGame::update(sf::RenderWindow& window)
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        finished = true;
        return;
    }

    float deltaTime = clock.restart().asSeconds();
    remainingTime -= deltaTime;

    // Timer écoulé = perdu
    if (remainingTime <= 0.f)
    {
        remainingTime = 0.f;
        finished = true;
        won = false;
        std::cout << "? Temps écoulé, vous avez perdu !\n";
        return;
    }

    // Détecter la touche pressée actuellement
    sf::Keyboard::Key pressedKey = sf::Keyboard::Key::Unknown;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) pressedKey = sf::Keyboard::Key::Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) pressedKey = sf::Keyboard::Key::Down;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) pressedKey = sf::Keyboard::Key::Left;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) pressedKey = sf::Keyboard::Key::Right;

    // Vérifier si c’est un nouvel appui
    if (pressedKey != sf::Keyboard::Key::Unknown && pressedKey != lastKeyPressed)
    {
        if (pressedKey == sequence[currentIndex])
        {
            // Bonne touche = passer à la suivante
            currentIndex++;
        }
        else
        {
            // Mauvaise touche = remettre à zéro l'indice seulement
            std::cout << "? Mauvaise flèche ! Recommencez depuis le début !\n";
            currentIndex = 0;
        }
    }

    lastKeyPressed = pressedKey;

    // Si toutes les flèches faites
    if (currentIndex >= sequence.size())
    {
        finished = true;
        won = true;
        std::cout << "?? Séquence terminée !\n";
    }

    // Dessin des flèches
    drawSequence(window);

    // Afficher le timer en haut à gauche
    sf::Text timerText(font2);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::Yellow);
    std::stringstream ss;
    ss << "Temps restant: " << (int)remainingTime;
    timerText.setString(ss.str());
    timerText.setPosition({ 10.f, 5.f });
    window.draw(timerText);
}

bool ArrowMiniGame::isFinished() const { return finished; }
bool ArrowMiniGame::playerWon() const { return won; }