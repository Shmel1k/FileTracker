#include <iostream>
#include "filetracker/filetracker.cpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No directory specified, exiting\n";
        return 0;
    }
    FileTracker f(argv[1]);
    f.checkDifferenceNotMulti();
    // f.printFilesHash();
    return 0;
}
