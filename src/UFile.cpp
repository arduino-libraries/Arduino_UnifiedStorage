#include "UFile.h"

#include <cstdio>

UFile::UFile() : fp(nullptr) {}

UFile::UFile(const char* path) : fp(nullptr), path(path) {}

UFile::~UFile() {
    close();
}

bool UFile::changeMode(FileMode mode) {
    close();
    return open(path.c_str(), mode);
}

bool UFile::open(const char* filename, FileMode fileMode) {
    const char* mode;

    path = filename;
    // Set the mode based on the fileMode
    switch (fileMode) {
        case READ:
            mode = "r+";
            break;
        case WRITE:
            mode = "w+";
            break;
        case APPEND:
            mode = "a+";
            break;
        default:
            mode = "r"; // Default mode is "read"
            break;
    }

    // Open the file
    fp = fopen(filename, mode);
    fm = fileMode;

    if (fp == nullptr) {
        // Failed to open the file
        return false;
    }

    return true;
}

bool UFile::open(String filename, FileMode mode) {
    return open(filename.c_str(), mode);
}

void UFile::close() {
    // Close the file
    if (fp != nullptr) {
        fclose(fp);
        //fp = nullptr;
    }
}

bool UFile::seek(size_t offset) {
    // Seek to a specific position in the file
    if (fp == nullptr) {
        // File pointer is not valid
        return false;
    }

    int result = fseek(fp, offset, SEEK_SET);
    return (result == 0);
}

int UFile::available() {
    // Check the available data in the file
    if (fp == nullptr) {
        // File pointer is not valid
        return 0;
    }

    int currentPosition = ftell(fp);
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fseek(fp, currentPosition, SEEK_SET);

    return (fileSize - currentPosition);
}

int UFile::read() {
    // Read a single byte from the file
    if (fp == nullptr) {
        // File pointer is not valid
        return 0;
    }

    int value = fgetc(fp);
    return value;
}

size_t UFile::read(uint8_t* buffer, size_t size) {
    // Read data from the file into the buffer
    if (fp == nullptr) {
        // File pointer is not valid
        return 0;
    }

    size_t bytesRead = fread(buffer, sizeof(uint8_t), size, fp);
    return bytesRead;
}

String UFile::readAsString() {
    if (fp == nullptr) {
        return String("");
    }

    this->seek(0);
    size_t bytesAvailable = this->available();
    uint8_t* buffer = new uint8_t[bytesAvailable + 1];
    this->read(buffer, bytesAvailable);

    String result = "";
    for (size_t i = 0; i < bytesAvailable; i++) {
        result += static_cast<char>(buffer[i]);
    }

    delete[] buffer;

    return result;
}

size_t UFile::write(uint8_t value) {
    // Write a single byte to the file
    if (fp == nullptr) {
        // File pointer is not valid
        return 0;
    }

    int result = fputc(value, fp);
    return (result != EOF) ? 1 : 0;
}

size_t UFile::write(String data) {
    if (fp == nullptr) {
        // File pointer is not valid
        return 0;
    }

    // Write data to the file
    size_t bytesWritten = fwrite(data.c_str(), sizeof(char), data.length(), fp);
    return bytesWritten;
}

size_t UFile::write(const uint8_t* buffer, size_t size) {
    if (fp == nullptr) {
        // File pointer is not valid
        return 0;
    }

    size_t bytesWritten = fwrite(buffer, sizeof(uint8_t), size, fp);
    return bytesWritten;
}

bool UFile::remove() {
    // Remove the file;
    if(this->exists() && !path.empty()){
            int result = ::remove(path.c_str());
            if (result == 0) {
                return true;
            } else {
                // Error occurred while removing the file
                return false;
            }
        } else {
            return false; // Handle the case when the path is not valid
        }
}

bool UFile::rename(const char* newFilename) {
    // Rename the file
    int result = ::rename(path.c_str(), newFilename);
    if (result == 0) {
        // Update the internal filename
        path = newFilename;
        return true;
    } else {
        // Error occurred while renaming the file
        return false;
    }
}

bool UFile::rename(String newFilename) {
    return rename(newFilename.c_str());
}

bool UFile::exists() {
    // Check if the file exists
    FILE* file = fopen(path.c_str(), "r");
    if (file != nullptr) {
        // File exists
        fclose(file);
        return true;
    } else {
        // File does not exist
        return false;
    }
}

bool UFile::copyTo(String destinationPath, bool overwrite) {
    return copyTo(destinationPath.c_str(), overwrite);
}

bool UFile::copyTo(Folder destinationFolder, bool overwrite) {
    const char* destinationPath = destinationFolder.getPath();
    return copyTo(destinationPath, overwrite);
}

bool UFile::copyTo(const char* destinationPath, bool overwrite) {
    std::string newPath = replaceFirstPathComponent(path, destinationPath);


    // Open the source file for reading
    FILE* sourceFile = fopen(path.c_str(), "r");

    if (sourceFile == nullptr) {
        return false;
    }

    FILE* destinationFile = fopen(newPath.c_str(), "r");

    if(destinationFile != nullptr){

        if(overwrite){
            fclose(destinationFile);
            ::remove(newPath.c_str());
        } else {
            errno = EEXIST;
            return false;
        }
    } 

    // Open the destination file for writing
    destinationFile = fopen(newPath.c_str(), "w");

    if (destinationFile == nullptr) {
        fclose(sourceFile);
        return false;
    }

    // Copy data from the source file to the destination file
    int c;
    while ((c = fgetc(sourceFile)) != EOF) {
        fputc(c, destinationFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    return true;
}

bool UFile::moveTo(String destinationPath, bool overwrite) {
    return moveTo(destinationPath.c_str());
}

bool UFile::moveTo(Folder destinationFolder, bool overwrite) {
    const char* destinationPath = destinationFolder.getPath();
    return moveTo(destinationPath);
}

bool UFile::moveTo(const char* destinationPath, bool overwrite){
    std::string newPath = replaceFirstPathComponent(path, destinationPath);

    FILE* destinationFile = fopen(newPath.c_str(), "r");

    fclose(fp);
    if (!copyTo(destinationPath, overwrite)) {
        return false; // Return false if the copy operation fails
    }

    // Delete the source file
    if (::remove(path.c_str())) {
        return false;
    }

    open(newPath.c_str(), fm); // sure about that ?
    path = newPath;

    return true;
}

Folder UFile::getParentFolder() {
    // Get the parent folder path
    size_t lastSlashPos = path.find_last_of('/');
    if (lastSlashPos != std::string::npos) {
        std::string parentPath = path.substr(0, lastSlashPos);
        return Folder(parentPath.c_str());
    } else {
        return Folder();
    }
}

const char* UFile::getPath() {
    return path.c_str();
}

String UFile::getPathAsString() {
    return String(path.c_str());
}
