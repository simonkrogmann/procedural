#pragma once

#include <QSettings>
#include <map>
#include <string>
#include <vector>

class Config
{
public:
    Config(const int argc, char * argv[]);
    ~Config();

    std::string value(const std::string& key);
    unsigned int valueUInt(const std::string& key);
    void setValue(const std::string& key, const unsigned int& value);
    std::vector<std::string> additionalArguments();
private:
    std::vector<std::string> toVector(const int& argc, char * argv[]);
    std::map<std::string, std::string> parseArguments(const std::vector<std::string>& arguments);
    void setValues(const std::map<std::string, std::string>& pairs);

    QSettings m_settings;
    std::vector<std::string> m_additionalArguments;

    const static std::map<std::string, std::string> defaults;
};
