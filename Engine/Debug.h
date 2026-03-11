#pragma once
#include <iostream>

extern bool debugF1;
extern bool debugF10;
extern bool debugF8;
extern bool debugF5;

class Debug
{
public:
	static void ChangeDebug(int i);
	static void DebugCout(std::string text, int F);

};
