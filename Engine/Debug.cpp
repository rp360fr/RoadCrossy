#include "Debug.h"

bool debugF1 = false;
bool debugF2 = false;
bool debugF3 = false;
bool debugF4 = false;

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
    case 2:
        debugF2 = !debugF2;

        if (debugF2)
            std::cout << "[  Activation Debug PosPlayer  ]" << std::endl;
        else
            std::cout << "[  Deactivation Debug PosPayer  ]" << std::endl;
        break;
    case 3:
        debugF3 = !debugF3;
        if (debugF3)
            std::cout << "[  Activation Debug hitbox  ]" << std::endl;
        else
            std::cout << "[  Deactivation Debug hitbox  ]" << std::endl;
        break;
    case 4:
        debugF4 = !debugF4;
        if (debugF4)
            std::cout << "[  Activation Debug sol  ]" << std::endl;
        else
            std::cout << "[  Deactivation Debug sol  ]" << std::endl;
        break;
    }
}


void Debug::DebugCout(std::string text, int F)
{
    switch (F)
    {
    case 1:
        if (debugF1)
        {
            std::cout << text << std::endl;
        }
        break;
    case 2:
        if (debugF2)
        {
            std::cout << text << std::endl;
        }
        break;
    case 3:
        if (debugF3)
        {
            std::cout << text << std::endl;
        }
    case 4:
        if (debugF4)
        {
            std::cout << text << std::endl;
        }
    }

}

