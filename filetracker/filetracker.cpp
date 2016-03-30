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

    for (int i = 0; i < fileNames.size(); ++i) {
        filesHash.insert(std::pair<std::string, size_t>(fileNames.at(i), getFileHash(fileNames.at(i))));
    }
    std::cout << "FileTracker has been successfully launched!\n";
}

FileTracker::~FileTracker() {
    //TODO Write destructror.
}

std::string FileTracker::readFile(std::string filename) {
    std::ifstream f(directory + filename);

    if (!f) {
        std::cout << "Error: Can not read file -- " << filename << " --";
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

void FileTracker::trackFile(std::string filename) {
    for (;;) {
        size_t hash = getFileHash(filename);
        if (hash != filesHash.at(filename)) {
            std::lock_guard<std::mutex> lock(locker);
            std::cout << "FILE " << filename << " HAS BEEN EDITED!!!\n";
            filesHash.at(filename) = hash;
            locker.unlock();
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void FileTracker::trackFilesNotMulti() {
    for (;;) {
        for (auto iter = fileNames.begin(); iter != fileNames.end(); ++iter) {
            std::lock_guard<std::mutex> lock(locker);
            size_t hash = getFileHash(*iter);
            if (hash != filesHash.at(*iter)) {
                std::cout << "File " << *iter << " has been edited!\n";
                filesHash.at(*iter) = hash;
            }
            locker.unlock();
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

void FileTracker::checkFileAdd() {
    for(;;) {

    struct dirent *ent;

    if ((dir = opendir(directory)) != NULL) {
        for (ent = readdir(dir); ent != NULL; ent = readdir(dir)) {
            if (!(std::find(fileNames.begin(), fileNames.end(), ent->d_name) != fileNames.end())) {
                std::cout << "File " << ent->d_name << " has been created!\n";
                fileNames.push_back(ent->d_name);
            }
        }
        closedir(dir);
    } else {
        std::cout << "Can not open directory";
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void FileTracker::checkDifferenceNotMulti() {
    std::thread addChecker(&FileTracker::checkFileAdd, this);
    std::thread fileChecker(&FileTracker::trackFilesNotMulti, this);

    addChecker.join();
    fileChecker.join();
}

void FileTracker::checkDifference() {
    std::vector<std::thread> threads;
    for (int i = 0; i < fileNames.size(); ++i) {
        std::string filename = fileNames.at(i);
        threads.push_back(std::thread(&FileTracker::trackFile, this, filename));
    }
    for (int i = 0; i < threads.size(); ++i) {
        threads.at(i).join();
    }
}

void FileTracker::printFileNames() {
    for (auto iter = fileNames.begin(); iter != fileNames.end(); ++iter) {
        std::cout << *iter << "\n";
    }
}

void FileTracker::printFilesHash() {
    for (auto iter = filesHash.begin(); iter != filesHash.end(); ++iter) {
        std::cout << iter->first << " " << iter->second << "\n";
    }
}
