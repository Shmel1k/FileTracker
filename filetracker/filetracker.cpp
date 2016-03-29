#include "filetracker.hpp"

FileTracker::FileTracker(const char* directory) {
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
    std::ifstream f(filename);

    if (!f) {
        return "";
    }

    std::stringstream buf;
    buf << f.rdbuf();
    return buf.str();
}

bool FileTracker::hasDirectoryEdited() {
    return _isEdited;
}

void FileTracker::checkDifference() {

}
