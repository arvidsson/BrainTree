#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace BrainTree {

class Blackboard
{
public:
    void setBool(std::string key, bool value) { bools[key] = value; }
    bool getBool(std::string key)
    {
        if (bools.find(key) == bools.end()) {
            bools[key] = false;
        }
        return bools[key];
    }
    bool hasBool(std::string key) const { return bools.find(key) != bools.end(); }

    void setInt(std::string key, int value)  { ints[key] = value; }
    int getInt(std::string key)
    {
        if (ints.find(key) == ints.end()) {
            ints[key] = 0;
        }
        return ints[key];
    }
    bool hasInt(std::string key) const  { return ints.find(key) != ints.end(); }

    void setFloat(std::string key, float value)  { floats[key] = value; }
    float getFloat(std::string key)
    {
        if (floats.find(key) == floats.end()) {
            floats[key] = 0.0f;
        }
        return floats[key];
    }
    bool hasFloat(std::string key) const  { return floats.find(key) != floats.end(); }

    void setDouble(std::string key, double value)  { doubles[key] = value; }
    double getDouble(std::string key)
    {
        if (doubles.find(key) == doubles.end()) {
            doubles[key] = 0.0f;
        }
        return doubles[key];
    }
    bool hasDouble(std::string key) const  { return doubles.find(key) != doubles.end(); }

    void setString(std::string key, std::string value)  { strings[key] = value; }
    std::string getString(std::string key)
    {
        if (strings.find(key) == strings.end()) {
            strings[key] = "";
        }
        return strings[key];
    }
    bool hasString(std::string key) const  { return strings.find(key) != strings.end(); }

    using Ptr = std::shared_ptr<Blackboard>;

protected:
    std::unordered_map<std::string, bool> bools;
    std::unordered_map<std::string, int> ints;
    std::unordered_map<std::string, float> floats;
    std::unordered_map<std::string, double> doubles;
    std::unordered_map<std::string, std::string> strings;
};

} // BrainTree
