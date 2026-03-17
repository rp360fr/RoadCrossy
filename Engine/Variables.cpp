#include "Component.h"

void Variables::addInt(const std::string& name, int value) {
    integers[name] = value;
}

void Variables::addFloat(const std::string& name, float value) {
    floats[name] = value;
}


void Variables::addString(const std::string& name, const std::string& value) {
    strings[name] = value;
}

