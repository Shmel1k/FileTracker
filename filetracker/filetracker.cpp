#include "filetracker.hpp"

FileTracker::FileTracker(std::string directory) {
    this->directory = directory;
}

FileTracker::~FileTracker() {

}

bool FileTracker::hasDirectoryEdited() {
    return _isEdited;
}

void FileTracker::checkDifference() {

}
