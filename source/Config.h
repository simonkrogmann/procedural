#pragma once

#include <QSettings>
#include <map>
#include <string>
#include <vector>

class Config
{
public:
    Config(int argc, char * argv[]);
    ~Config();

    std::string value(const std::string& key);
    int valueInt(const std::string& key);
    void setValueInt(const std::string& key, const int& value);
    std::vector<std::string> additionalArguments();
private:
    std::vector<std::string> toVector(int argc, char * argv[]);
    std::map<std::string, std::string> parseArguments(std::vector<std::string> arguments);
    void setValues(std::map<std::string, std::string> pairs);

    QSettings m_settings;
    std::vector<std::string> m_additionalArguments;

    const static std::map<std::string, std::string> defaults;
};
