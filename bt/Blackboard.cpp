#include "Blackboard.hpp"

namespace bt
{

void Blackboard::SetBool(std::string key, bool value)
{
    bools[key] = value;
}

bool Blackboard::GetBool(std::string key)
{
    if (bools.find(key) == bools.end()) {
        bools[key] = false;
    }
    return bools[key];
}

bool Blackboard::HasBool(std::string key) const
{
    return bools.find(key) != bools.end();
}

void Blackboard::SetInt(std::string key, int value)
{
    ints[key] = value;
}

int Blackboard::GetInt(std::string key)
{
    if (ints.find(key) == ints.end()) {
        ints[key] = 0;
    }
    return ints[key];
}

bool Blackboard::HasInt(std::string key) const
{
    return ints.find(key) != ints.end();
}

void Blackboard::SetFloat(std::string key, float value)
{
    floats[key] = value;
}

float Blackboard::GetFloat(std::string key)
{
    if (floats.find(key) == floats.end()) {
        floats[key] = 0.0f;
    }
    return floats[key];
}

bool Blackboard::HasFloat(std::string key) const
{
    return floats.find(key) != floats.end();
}

void Blackboard::SetDouble(std::string key, double value)
{
    doubles[key] = value;
}

double Blackboard::GetDouble(std::string key)
{
    if (doubles.find(key) == doubles.end()) {
        doubles[key] = 0.0f;
    }
    return doubles[key];
}

bool Blackboard::HasDouble(std::string key) const
{
    return doubles.find(key) != doubles.end();
}

void Blackboard::SetString(std::string key, std::string value)
{
    strings[key] = value;
}

std::string Blackboard::GetString(std::string key)
{
    if (strings.find(key) == strings.end()) {
        strings[key] = "";
    }
    return strings[key];
}

bool Blackboard::HasString(std::string key) const
{
    return strings.find(key) != strings.end();
}

}
