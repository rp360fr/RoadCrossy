#pragma once
#include <iostream>

extern bool debugF1;
extern bool debugF2;

class Debug
{
public:
	static void ChangeDebug(int i);
	static void DebugCout(std::string text, int F);

};
