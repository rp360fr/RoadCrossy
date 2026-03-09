#include "Debug.h"

bool debugF9 = false;
bool debugF10 = false;
bool debugF8 = false;
bool debugF5 = false;

void Debug::ChangeDebug(int i)
{
    switch (i)
    {
    case 1:
        debugF9 = !debugF9;

        if (debugF9)
            std::cout << "[  Activation Debug Pnj1  ]" << std::endl;
        else
            std::cout << "[  Deactivation Debug Pnj1 ]" << std::endl;
        break;
    case 2:
        debugF10 = !debugF10;

        if (debugF10)
            std::cout << "[  Activation Debug Pnj2  ]" << std::endl;
        else
            std::cout << "[  Deactivation Debug Pnj2 ]" << std::endl;
        break;
    case 3:
        debugF8 = !debugF8;

        if (debugF8)
            std::cout << "[  Activation Debug Joueur  ]" << std::endl;
        else
            std::cout << "[  Deactivation Debug Joueur ]" << std::endl;
        break;
    case 5:
        debugF5 = !debugF5;

        if (debugF5)
            std::cout << "[  Activation Debug Map  ]" << std::endl;
        else
            std::cout << "[  Deactivation Debug Map ]" << std::endl;
        break;
    }


}


void Debug::DebugCout(std::string text, int F)
{
    switch (F)
    {
    case 8:
        if (debugF8)
        {
            std::cout << text << std::endl;
        }
        break;
    case 9:
        if (debugF9)
        {
            std::cout << text << std::endl;
        }
        break;
    case 10:
        if (debugF10)
        {
            std::cout << text << std::endl;
        }
        break;
    }

}

