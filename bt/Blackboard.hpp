#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace bt
{

class Blackboard
{
public:
    static Blackboard& GetInstance()
    {
        static Blackboard instance;
        return instance;
    }

    void SetBool(std::string key, bool value);
    bool GetBool(std::string key);
    bool HasBool(std::string key) const;

    void SetInt(std::string key, int value);
    int GetInt(std::string key);
    bool HasInt(std::string key) const;

    void SetFloat(std::string key, float value);
    float GetFloat(std::string key);
    bool HasFloat(std::string key) const;

    void SetDouble(std::string key, double value);
    float GetDouble(std::string key);
    bool HasDouble(std::string key) const;

    void SetString(std::string key, std::string value);
    std::string GetString(std::string key);
    bool HasString(std::string key) const;

    using Ptr = std::shared_ptr<Blackboard>;

protected:
    std::unordered_map<std::string, bool> bools;
    std::unordered_map<std::string, int> ints;
    std::unordered_map<std::string, float> floats;
    std::unordered_map<std::string, double> doubles;
    std::unordered_map<std::string, std::string> strings;
};

}
