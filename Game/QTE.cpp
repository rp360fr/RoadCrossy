#include "QTE.h"
#include <iostream>
#include "Scene.h"

ArrowMiniGame::ArrowMiniGame()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    sequenceLength = 4;      // 20 flèches
    remainingTime = 5.f;     // 20 secondes
    finished = false;
    currentIndex = 0;
    won = false;
    windowWidth = 800.f;   // ou passe la window en paramètre
    windowHeight = 800.f;
    generateSequence(sequenceLength);
    text = nullptr;
    timerObj = nullptr;

    //    if (!font.openFromFile("./Assets/ArrowSymbols.ttf"))
    //        std::cerr << "Impossible de charger la police !\n";
    //    if (!font2.openFromFile("./Assets/3270NerdFont-Regular.ttf"))
    //        std::cerr << "Impossible de charger la police !\n";

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

void ArrowMiniGame::drawSequence(Scene* lvl)
{
    const float startX = 10.f;
    const float y = 400.f;
    const float spacing = 50.f;

    if (text == nullptr)
    {
        // Créer un GameObject par flèche
        for (size_t i = 0; i < sequence.size(); ++i)
        {
            std::string arrow;
            switch (sequence[i])
            {
            case sf::Keyboard::Key::Up:    arrow = "D"; break;
            case sf::Keyboard::Key::Down:  arrow = "B"; break;
            case sf::Keyboard::Key::Left:  arrow = "C"; break;
            case sf::Keyboard::Key::Right: arrow = "A"; break;
            default: arrow = "?"; break;
            }

            float posX = startX + i * spacing;
            // Flèche courante en jaune, les autres en blanc
            sf::Color color = (i == currentIndex) ? sf::Color::Yellow : sf::Color::White;

            GameObject* arrow_obj = new GameObject(sf::Vector2f(posX, y));
            Text* t = new Text(arrow, 40, color, "ArrowSymbols.ttf");
            arrow_obj->AddComponent(t);
            lvl->AddParamObject(arrow_obj);
            arrow_obj->Start();
            arrowObjects.push_back(arrow_obj); // ← stocker tous les objets
        }
        text = arrowObjects[0]; // ← text pointe sur le premier pour le hide()
    }
    else
    {
        // Mettre à jour les couleurs chaque frame
        for (size_t i = 0; i < arrowObjects.size(); ++i)
        {
            sf::Color color = (i < currentIndex) ? sf::Color::Green  // déjà faite
                : (i == currentIndex) ? sf::Color::Yellow  // courante
                : sf::Color::White;  // à faire
            arrowObjects[i]->GetComponent<Text>()->setColor(color);
        }
    }
}

void ArrowMiniGame::update(Scene* lvl)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        finished = true;
        return;
    }

    float deltaTime = clock.restart().asSeconds();
    remainingTime -= deltaTime;

    if (remainingTime <= 0.f)
    {
        remainingTime = 0.f;
        finished = true;
        won = false;
        return;
    }

    sf::Keyboard::Key pressedKey = sf::Keyboard::Key::Unknown;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    pressedKey = sf::Keyboard::Key::Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  pressedKey = sf::Keyboard::Key::Down;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  pressedKey = sf::Keyboard::Key::Left;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) pressedKey = sf::Keyboard::Key::Right;

    if (pressedKey != sf::Keyboard::Key::Unknown && pressedKey != lastKeyPressed)
    {
        if (pressedKey == sequence[currentIndex])
            currentIndex++;
        else
            currentIndex = 0;
    }
    lastKeyPressed = pressedKey;

    if (currentIndex >= sequence.size())
    {
        finished = true;
        won = true;
        return;
    }

    drawSequence(lvl);

    // Timer
    if (timerObj == nullptr)
    {
        timerObj = new GameObject(sf::Vector2f{ 10.f, 5.f });
        Text* timerComp = new Text("Timer", 20, sf::Color::Yellow, "PressStart2P-Regular.ttf");
        timerObj->AddComponent(timerComp); // ← manquait dans ton code original
        lvl->AddParamObject(timerObj);     // ← AddParamObject, pas AddGameObject
        timerObj->Start();
    }
    else
    {
        std::stringstream ss;
        ss << "Temps: " << (int)remainingTime;
        timerObj->GetComponent<Text>()->setText(ss.str());
    }
}

void ArrowMiniGame::hide(Scene * lvl)
{

    for (GameObject* obj : arrowObjects)
    {
        if (obj != nullptr)
            lvl->RemoveParamObject(obj);
    }
    arrowObjects.clear();
    text = nullptr;
    timerObj = nullptr;
    
}
bool ArrowMiniGame::isFinished() const { return finished; }
bool ArrowMiniGame::playerWon() const { return won; }