#include "Folder.h"
#include <Arduino.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

Folder::Folder() {}

Folder::Folder(const char* path) {

    DIR* dir = opendir(path);
    if (dir != nullptr) {
        this->path = std::string(path);
        closedir(dir);
    } else {
        int result = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
        if (result == 0) {
            this->path = std::string(path);

        } // else ...not sure about this one yet
    }
}

Folder::Folder(String dirname) {
 Folder(dirname.c_str());
}

UFile Folder::createFile(const char* fileName, FileMode fmode) {
    std::string filePath = this->path + "/" + fileName;
    UFile thisFile;
    thisFile.open(filePath.c_str(), fmode);
    return thisFile;
}

UFile Folder::createFile(String fileName, FileMode fmode) {
    return this->createFile(fileName.c_str(), fmode);
}

bool Folder::remove() {
    // Remove all files in the directory
    if(this->exists()){
        std::vector<UFile> files = this->getFiles();
        for (UFile file : files) {
 
            file.remove();

        }

        // Remove all subfolders in the directory
        std::vector<Folder> folders = this->getFolders();
        for (Folder directory : folders) {
            directory.remove();
        }

        // Remove the current directory
        if (::remove(this->path.c_str()) == 0) {
            return true;
        } else {
            // Error occurred while removing the directory
            return false;
        }
    }
 
}

bool Folder::rename(const char* newDirname) {
    // Rename the directory
    std::string newPath = replaceLastPathComponent(this->path, newDirname);

    // actually perform the POSIX command to rename the folder
    int result = ::rename(this->path.c_str(), newPath.c_str());
    if (result == 0) {
        // Update the internal directory path
        this->path = newPath;
        return true;
    } else {
        // Error occurred while renaming the directory
        return false;
    }
}

bool Folder::rename(String newDirname) {
    return this->rename(newDirname.c_str());
}

bool Folder::exists() {
    // Check if the directory exists
    DIR* dir = opendir(this->path.c_str());
    if (dir != nullptr) {
        // Folder exists
        closedir(dir);
        return true;
    } else {
        // Folder does not exist
        return false;
    }
}

const char* Folder::getPath() {
    return this->path.c_str();
}

String Folder::getPathAsString() {
    return String(this->getPath());
}

Folder Folder::createSubfolder(const char* subfolderName, bool overwrite) {
    std::string subfolderPath = this->path + "/" + subfolderName;

    DIR* dir = opendir(subfolderPath.c_str());
    if (dir != nullptr) {
        if(!overwrite){
            errno = EEXIST;
            closedir(dir);
            return Folder(subfolderPath.c_str());

        } else {
            closedir(dir);
            Folder(subfolderPath.c_str()).remove();
        }   
    } 


    int result = mkdir(subfolderPath.c_str(), 0777);
    if (result == 0) {
        return Folder(subfolderPath.c_str());
    } else {
        return Folder();
    }

 
}

Folder Folder::createSubfolder(String subfolderName, bool overwrite)  {
    return this->createSubfolder(subfolderName.c_str(), overwrite);
}

std::vector<UFile> Folder::getFiles() {
    std::vector<UFile> ret;
    DIR* directory = opendir(this->path.c_str());
    if (directory != nullptr) {
        struct dirent* entry;
        while ((entry = readdir(directory)) != nullptr) {
            if (entry->d_type == DT_REG) { // Regular file
                std::string filePath = this->path + "/" + std::string(entry->d_name);
                ret.push_back(UFile(filePath.c_str()));
            }
        }
        closedir(directory);
        return ret;
    } else {
        return std::vector<UFile>();
    }
}

std::vector<Folder> Folder::getFolders() {
    std::vector<Folder> ret;

    DIR* directory = opendir(this->path.c_str());
    if (directory != nullptr) {
        struct dirent* entry;
        while ((entry = readdir(directory)) != nullptr) {
            if (entry->d_type == DT_DIR) { // Folder
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                    std::string subfolderPath = this->path + "/" + std::string(entry->d_name);
                    ret.push_back(Folder(subfolderPath.c_str()));
                }
            }
        }
        closedir(directory);
        return ret;
    } else {
        return std::vector<Folder>();
    }
}

bool Folder::copyTo(Folder destination, bool overwrite) {
    return this->copyTo(destination.getPath(), overwrite);
}



bool Folder::copyTo(const char* destinationPath, bool overwrite) {
    std::string source = this->path;
    std::string fileName = getLastPathComponent(this->path.c_str());
    std::string destination = std::string(destinationPath) + "/" + fileName;

    DIR* dir = opendir(source.c_str());
    if (dir == nullptr) {
        return false;
    }


    if(opendir(destination.c_str())){
        if(overwrite){
            Folder(destination.c_str()).remove();
        } else {
            return false;
        }

    } else  if (mkdir(destination.c_str(), 0777) != 0 && errno != EEXIST) {
        closedir(dir);
    }

    // Create destination directory if it doesn't exist


    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            std::string sourcePath = source + "/" + std::string(entry->d_name);
            std::string destinationPath = destination + "/" + std::string(entry->d_name);

            struct stat fileInfo;
            if (stat(sourcePath.c_str(), &fileInfo) != 0) {
                closedir(dir);
                return false;
            }

            if (S_ISDIR(fileInfo.st_mode)) {
                if (!copyFolder(sourcePath.c_str(), destinationPath.c_str())) {
                    closedir(dir);
                    return false;
                }
            } else {
                // Copy regular files
                FILE* sourceFile = fopen(sourcePath.c_str(), "r");
                if (sourceFile == nullptr) {
                    closedir(dir);
                    return false;
                }

                FILE* destinationFile = fopen(destinationPath.c_str(), "w");
                if (destinationFile == nullptr) {
                    fclose(sourceFile);
                    closedir(dir);
                    return false;
                }

                int c;
                while ((c = fgetc(sourceFile)) != EOF) {
                    fputc(c, destinationFile);
                }

                fclose(sourceFile);
                fclose(destinationFile);
            }
        }
    }

    closedir(dir);
    return true;
}


bool Folder::copyTo(String destination, bool overwrite) { 
    return this->copyTo(destination.c_str(), overwrite);
}

bool Folder::moveTo(Folder destination, bool overwrite) {
    return this->moveTo(destination.getPath(), overwrite);
}

bool Folder::moveTo(const char* destination, bool overwrite) {
    std::string newPath = replaceFirstPathComponent(this->path.c_str(), destination);



    if (!this->copyTo(destination, overwrite)) {
        return false; // Return false if the copy operation fails
    } else {
        if (::remove(this->path.c_str()) != 0) {
            return false;
        }
    }

    this->path = newPath;
    return true;
}

bool Folder::moveTo(String destination, bool overwrite) {
    return this->moveTo(destination.c_str(), overwrite);
}
