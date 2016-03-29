#pragma once

#include <string>
#include <map>
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

    void printFileNames();
    void printFilesHash();

private:
    DIR *dir; //directory we scan
    const char* directory; //the directory we are in.
    std::vector<std::string> fileNames; //we get file names, then scan them.
    std::map<std::string, size_t> filesHash;
    size_t getFileHash(std::string filename);
    std::string readFile(std::string filename); //we read file and get string
    void checkDifference(); //function that checks difference.
    void trackFile(std::string filename);
};
