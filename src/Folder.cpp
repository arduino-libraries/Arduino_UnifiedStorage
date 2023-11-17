#include "Arduino_UnifiedStorage.h"
#include "Folder.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>

Folder::Folder() {}

Folder::Folder(const char* path) {

    DIR* dir = opendir(path);
    if (dir != nullptr) {
        this->path = std::string(path);
        Arduino_UnifiedStorage::debugPrint("[Folder][INFO] Folder already existing, opening : " + String(path));
        closedir(dir);
    } else {
        int result = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
        if (result == 0) {
            this->path = std::string(path);
            Arduino_UnifiedStorage::debugPrint("[Folder][INFO] Created folder: " + String(this->path.c_str()));
        } else {
            Arduino_UnifiedStorage::debugPrint("[Folder][ERROR] Failed to create folder: " + String(path));
        }
    }
}

Folder::Folder(String dirname) {
 Folder(dirname.c_str());
}

UFile Folder::createFile(const char* fileName, FileMode fmode) {
    std::string filePath = this->path + "/" + fileName;
    Arduino_UnifiedStorage::debugPrint("[Folder][createFile][INFO] Creating file: " + String(filePath.c_str()));
    UFile thisFile;
    thisFile.open(filePath.c_str(), fmode);
    return thisFile;
}

UFile Folder::createFile(String fileName, FileMode fmode) {
    return this->createFile(fileName.c_str(), fmode);
}

bool Folder::remove() {
    // Check if the directory exists
    if(!this->exists()){
        Arduino_UnifiedStorage::debugPrint("[Folder][remove][ERROR] Folder does not exist");
        return false;
    }

    Arduino_UnifiedStorage::debugPrint("[Folder][remove][INFO] Removing all files and folders in path: " + String(this->path.c_str()));
    // Remove all files in the directory
    std::vector<UFile> files = this->getFiles();
    for (UFile file : files) {
        file.remove();
        Arduino_UnifiedStorage::debugPrint("[Folder][remove][INFO] Removing file: " + String(file.getPathAsString()));
    }

    // Remove all subfolders in the directory
    std::vector<Folder> folders = this->getFolders();
    for (Folder directory : folders) {
        directory.remove();
        Arduino_UnifiedStorage::debugPrint("[Folder][remove][INFO] Removing folder: " + String(directory.getPathAsString()));
    }

    // Remove the current directory
    if (::remove(this->path.c_str()) == 0) {
        Arduino_UnifiedStorage::debugPrint("[Folder][remove][INFO] Removed current folder: " + String(this->path.c_str()));
        return true;
    } else {
        // Error occurred while removing the directory
        Arduino_UnifiedStorage::debugPrint("[Folder][remove][ERROR] Failed to remove current folder: " + String(this->path.c_str()));
        return false;
    }
}

bool Folder::rename(const char* newDirname) {
    // Rename the directory
    std::string newPath = replaceLastPathComponent(this->path, newDirname);

    // actually perform the POSIX command to rename the folder
    Arduino_UnifiedStorage::debugPrint("[Folder][rename][INFO] Renaming folder: " + String(this->path.c_str()) + " to " + String(newPath.c_str()));
    int result = ::rename(this->path.c_str(), newPath.c_str());
    if (result == 0) {
        // Update the internal directory path
        this->path = newPath;
        Arduino_UnifiedStorage::debugPrint("[Folder][rename][INFO] Successfully renamed folder: " + String(this->path.c_str()));
        return true;
    } else {
        // Error occurred while renaming the directory
        Arduino_UnifiedStorage::debugPrint("[Folder][rename][ERROR] Failed to rename folder");
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
            Arduino_UnifiedStorage::debugPrint("[Folder][createSubfolder][INFO] Folder already exists: " + String(subfolderPath.c_str()));
            return Folder(subfolderPath.c_str());

        } else {
            closedir(dir);
            Arduino_UnifiedStorage::debugPrint("[Folder][createSubfolder][INFO] Overwriting existing folder: " + String(subfolderPath.c_str()));
            Folder(subfolderPath.c_str()).remove();
        }   
    } 


    int result = mkdir(subfolderPath.c_str(), 0777);
    if (result == 0) {
        Arduino_UnifiedStorage::debugPrint("[Folder][createSubfolder][INFO] Folder created: " + String(subfolderPath.c_str()));
        return Folder(subfolderPath.c_str());
    } else {
        Arduino_UnifiedStorage::debugPrint("[Folder][createSubfolder][ERROR] Failed to create folder: " + String(subfolderPath.c_str()));
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
        Arduino_UnifiedStorage::debugPrint("[Folder][getFiles][INFO] " + String(ret.size()) + " files found in folder: " + String(this->path.c_str()));
        return ret;
    } else {
        Arduino_UnifiedStorage::debugPrint("[Folder][getFiles][INFO] Failed to open folder: " + String(this->path.c_str()));
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
        Arduino_UnifiedStorage::debugPrint("[Folder][getFolders][INFO] " + String(ret.size()) + " folders found in folder: " + String(this->path.c_str()));
        return ret;
    } else {
        Arduino_UnifiedStorage::debugPrint("[Folder][getFolders][ERROR] Failed to open folder: " + String(this->path.c_str()));
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
        Arduino_UnifiedStorage::debugPrint("[Folder][copyTo][INFO] Failed to open source folder: " + String(source.c_str()));
        return false;
    }

    if(opendir(destination.c_str())){
        if(overwrite){
            Arduino_UnifiedStorage::debugPrint("[Folder][copyTo][INFO] Overwriting existing folder: " + String(destination.c_str()));
            Folder(destination.c_str()).remove();
        } else {
            Arduino_UnifiedStorage::debugPrint("[Folder][copyTo][INFO] Destination folder already exists and overwrite is disabled: " + String(destination.c_str()));
            return false;
        }

    } else  if (mkdir(destination.c_str(), 0777) != 0 && errno != EEXIST) {
        Arduino_UnifiedStorage::debugPrint("[Folder][copyTo][ERROR] Failed to create destination folder: " + String(destination.c_str()));
        closedir(dir);
        return false;
    }

    // Create destination directory if it doesn't exist
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            std::string sourcePath = source + "/" + std::string(entry->d_name);
            std::string destinationPath = destination + "/" + std::string(entry->d_name);

            struct stat fileInfo;
            if (stat(sourcePath.c_str(), &fileInfo) != 0) {
                Arduino_UnifiedStorage::debugPrint("[Folder][copyTo][ERROR] Failed to get file info for source file: " + String(sourcePath.c_str()));
                closedir(dir);
                return false;
            }

            if (S_ISDIR(fileInfo.st_mode)) {
                if (!copyFolder(sourcePath.c_str(), destinationPath.c_str())) {
                    Arduino_UnifiedStorage::debugPrint("[Folder][copyTo][ERROR] Failed to copy subfolder: " + String(sourcePath.c_str()));
                    closedir(dir);
                    return false;
                }
            } else {
                // Copy regular files
                FILE* sourceFile = fopen(sourcePath.c_str(), "r");
                if (sourceFile == nullptr) {
                    Arduino_UnifiedStorage::debugPrint("[Folder][copyTo][ERROR] Failed to open source file: " + String(sourcePath.c_str()));
                    closedir(dir);
                    return false;
                }

                FILE* destinationFile = fopen(destinationPath.c_str(), "w");
                if (destinationFile == nullptr) {
                    Arduino_UnifiedStorage::debugPrint("[Folder][copyTo][ERROR] Failed to create destination file: " + String(destination.c_str()));
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
    Arduino_UnifiedStorage::debugPrint("[Folder][copyTo][INFO] Folder copied to: " + String(destination.c_str()));
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
        Arduino_UnifiedStorage::debugPrint("[Folder][moveTo][ERROR]  Failed to copy folder to destination: " +  String(destination));
        return false; // Return false if the copy operation fails
    } else {
        if (::remove(this->path.c_str()) != 0) {
            Arduino_UnifiedStorage::debugPrint("[Folder][moveTo][ERROR] Failed to remove original folder: " + String(this->path.c_str()));
            return false;
        }
    }

    this->path = newPath;
    Arduino_UnifiedStorage::debugPrint("[Folder][moveTo][INFO]  Folder moved to: " + String(newPath.c_str()));
    return true;
}

bool Folder::moveTo(String destination, bool overwrite) {
    return this->moveTo(destination.c_str(), overwrite);
}
