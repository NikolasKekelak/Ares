//
// Created by nikolas on 5/13/26.
//

#ifndef ARES_FILEMANAGER_H
#define ARES_FILEMANAGER_H
#include <vector>
#include <bits/locale_conv.h>
#include <sys/stat.h>

// humbly stolen from https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
inline bool file_exists (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

class FileManager {

    static std::vector<std::string> files;
    static int count;
public:
    static void addFile(std::string path);
    static std::string getNextFile();
};



#endif //ARES_FILEMANAGER_H
