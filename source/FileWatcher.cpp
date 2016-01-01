#include "FileWatcher.h"

#include <string>
#include <cassert>
#include <sys/stat.h>

FileWatcher::FileWatcher()
: m_files { }
{

}

FileWatcher::~FileWatcher()
{

}

void FileWatcher::addFile(const std::string& file)
{
    m_files[file] = timeStamp(file);
}


void FileWatcher::removeFile(const std::string& file)
{

}

bool FileWatcher::check()
{
    bool changed = false;
    for (const auto& file : m_files)
    {
        const auto newTime = timeStamp(file.first);
        if (newTime != file.second)
        {
            m_files[file.first] = newTime;
            changed = true;
        }
    }
    return changed;
}

time_t FileWatcher::timeStamp(const std::string& file)
{
    struct stat stats;
    const auto error = stat(file.c_str(), &stats);
    assert(error == 0);
    return stats.st_mtime;
}
