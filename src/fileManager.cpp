//
// Created by nikolas on 5/13/26.
//

#include "fileManager.h"

#include "Ares/Ares.h"
#include "ErrorHandling/ErrorHandler.h"

int FileManager::count = 0;
std::vector<std::string> FileManager::files;

void FileManager::addFile(std::string path) {
    if (!file_exists(path)) {
        Ares::error(FILE_NOT_FOUND, path);
    }
    files.push_back(path);
}

std::string FileManager::getNextFile() {
    return files[count++];
}


