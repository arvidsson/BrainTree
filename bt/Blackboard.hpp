#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace bt
{

class Blackboard
{
public:
    void SetBool(std::string key, bool value) { bools[key] = value; }
    bool GetBool(std::string key)
    {
        if (bools.find(key) == bools.end()) {
            bools[key] = false;
        }
        return bools[key];
    }
    bool HasBool(std::string key) const { return bools.find(key) != bools.end(); }

    void SetInt(std::string key, int value)  { ints[key] = value; }
    int GetInt(std::string key)
    {
        if (ints.find(key) == ints.end()) {
            ints[key] = 0;
        }
        return ints[key];
    }
    bool HasInt(std::string key) const  { return ints.find(key) != ints.end(); }

    void SetFloat(std::string key, float value)  { floats[key] = value; }
    float GetFloat(std::string key)
    {
        if (floats.find(key) == floats.end()) {
            floats[key] = 0.0f;
        }
        return floats[key];
    }
    bool HasFloat(std::string key) const  { return floats.find(key) != floats.end(); }

    void SetDouble(std::string key, double value)  { doubles[key] = value; }
    double GetDouble(std::string key)
    {
        if (doubles.find(key) == doubles.end()) {
            doubles[key] = 0.0f;
        }
        return doubles[key];
    }
    bool HasDouble(std::string key) const  { return doubles.find(key) != doubles.end(); }

    void SetString(std::string key, std::string value)  { strings[key] = value; }
    std::string GetString(std::string key)
    {
        if (strings.find(key) == strings.end()) {
            strings[key] = "";
        }
        return strings[key];
    }
    bool HasString(std::string key) const  { return strings.find(key) != strings.end(); }

    using Ptr = std::shared_ptr<Blackboard>;

protected:
    std::unordered_map<std::string, bool> bools;
    std::unordered_map<std::string, int> ints;
    std::unordered_map<std::string, float> floats;
    std::unordered_map<std::string, double> doubles;
    std::unordered_map<std::string, std::string> strings;
};

}
