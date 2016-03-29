#pragma once

#include <string>
#include <vector>
#include <thread>
#include <utility>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <sstream>

class FileTracker {
public:
    FileTracker(const char* directory);
    ~FileTracker();

    bool hasDirectoryEdited();
private:
    DIR *dir; //directory we scan
    std::vector<std::string> fileNames; //we get file names, then scan them.
    std::hash<std::string> filesHash;
    std::string readFile(std::string filename); //we read file and get string
    bool _isEdited; //our result
    void checkDifference(); //function that checks difference.
};
