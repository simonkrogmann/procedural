#include "Config.h"

#include <string>
#include <vector>
#include <map>
#include <cassert>

#include <QSettings>

#include "util.h"

Config::Config(int argc, char * argv[])
: m_settings {"simonkrogmann", "procedural"}
{
    const auto arguments = toVector(argc, argv);
    const auto options = parseArguments(arguments);

    setValues(options);
    m_settings.sync();
}

Config::~Config()
{

}

std::vector<std::string> Config::toVector(int argc, char * argv[])
{
    std::vector<std::string> arguments;
    for (int i = 0; i < argc; ++i)
    {
        arguments.push_back(argv[i]);
    }
    return arguments;
}

std::map<std::string, std::string> Config::parseArguments(std::vector<std::string> arguments)
{
    std::map<std::string, std::string> options;
    for (const auto& argument : arguments)
    {
        if (argument.substr(0, 2) == "--" && util::contains(argument, "="))
        {
            auto split = util::split(argument.substr(2), "=");
            options[split.first] = split.second;
        }
        else
        {
            m_additionalArguments.push_back(argument);
        }
    }
    return options;
}

std::vector<std::string> Config::additionalArguments()
{
    return m_additionalArguments;
}


void Config::setValues(std::map<std::string, std::string> pairs)
{
    for (const auto& pair : pairs)
    {
        if (defaults.find(pair.first) != defaults.end())
        {
            m_settings.setValue(QString::fromStdString(pair.first),
                QString::fromStdString(pair.second));
        }
    }
}

std::string Config::value(const std::string& key)
{
    assert(defaults.find(key) != defaults.end());
    auto setting = m_settings.value(QString::fromStdString(key),
        QString::fromStdString(defaults.at(key)));
    return setting.toString().toUtf8().constData();
}

const std::map<std::string, std::string> Config::defaults {
    {"gl-version", "best"},
    {"file-resolution", "3840x2160"},
};
