#include "Debug.h"

bool debugF1 = false;
bool debugF10 = false;
bool debugF8 = false;
bool debugF5 = false;

void Debug::ChangeDebug(int i)
{
    switch (i)
    {
    case 1:

        debugF1 = !debugF1;

        if (debugF1)
            std::cout << "[  Activation Scrolling  ]" << std::endl;
        else
            std::cout << "[  Deactivation Scrolling ]" << std::endl;
        break;
    case 10:
        debugF10 = !debugF10;

        if (debugF10)
            std::cout << "[  Activation Debug Pnj2  ]" << std::endl;
        else
            std::cout << "[  Deactivation Debug Pnj2 ]" << std::endl;
        break;
    case 8:
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
    case 1:
        if (debugF1)
        {
            std::cout << text << std::endl;
        }
        break;
    case '10':
        if (debugF10)
        {
            std::cout << text << std::endl;
        }
        break;
    }

}

