#pragma once

#include <string>
#include <map>
#include <functional>

class FileWatcher
{
public:
    FileWatcher();
    ~FileWatcher();

    void addFile(const std::string& file);
    void removeFile(const std::string& file);
    bool check();
private:
    time_t timeStamp(const std::string& file);

    std::map<std::string, time_t> m_files;
};
