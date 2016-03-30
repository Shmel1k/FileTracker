#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <sstream>
#include <chrono>
#include <mutex>
#include <algorithm> //TODO sort included headers by name.

class FileTracker {
public:
    FileTracker(const char* directory);
    ~FileTracker();

    void printFileNames();
    void printFilesHash();
    void checkDifference(); //function that checks difference.
    void checkDifferenceNotMulti();
    void checkFileAdd();
private:
    DIR *dir; //directory we scan
    const char* directory; //the directory we are in.
    std::vector<std::string> fileNames; //we get file names, then scan them.
    std::map<std::string, size_t> filesHash;
    size_t getFileHash(std::string filename);
    std::string readFile(std::string filename); //we read file and get string

    void trackFilesNotMulti();
    void trackFile(std::string filename);

    std::mutex locker;
};
