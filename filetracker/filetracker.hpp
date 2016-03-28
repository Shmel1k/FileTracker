#pragma once

#include <string>
#include <vector>
#include <thread>
#include <dirent.h>

class FileTracker {
public:
    FileTracker(std::string directory);
    ~FileTracker();

    bool hasDirectoryEdited();
private:
    DIR *directory; //directory we scan
    std::vector<std::string> fileNames; //we get file names, then scan them;
    bool _isEdited; //our result
    void checkDifference(); //function that checks difference.
};
