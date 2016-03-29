#include "filetracker.hpp"

FileTracker::FileTracker(const char* directory) {
    this->directory = directory;

    struct dirent *ent;

    if ((dir = opendir(directory)) != NULL) {
        for (ent = readdir(dir); ent != NULL; ent = readdir(dir)) {
            fileNames.push_back(ent->d_name);

        }
        closedir(dir);
    } else {
        std::cout << "Can not open directory";
        return;
    }
}

FileTracker::~FileTracker() {

}

std::string FileTracker::readFile(std::string filename) {
    std::ifstream f(directory + filename);

    if (!f) {
        return "";
    }

    std::stringstream buf;
    buf << f.rdbuf();
    return buf.str();
}

size_t FileTracker::getFileHash(std::string filename) {
    std::hash<std::string> h;
    return h(readFile(filename));
}

void FileTracker::checkDifference() {

}

void FileTracker::printHashes() {
    for (auto iter = filesHash.begin(); iter != filesHash.end(); ++iter) {
        std::cout << *iter << "\n";
    }
}

void FileTracker::printFileNames() {
    for (auto iter = fileNames.begin(); iter != fileNames.end(); ++iter) {
        std::cout << *iter << "\n";
    }
}
