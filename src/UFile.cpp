#include "UFile.h"

#include <cstdio>

UFile::UFile() : filePointer(nullptr) {}

UFile::UFile(const char* path) : filePointer(nullptr), path(path) {}

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
    filePointer = fopen(filename, mode);
    this -> fileMode = fileMode;

    if (filePointer == nullptr) {
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
    if (filePointer != nullptr) {
        fclose(filePointer);
    }
}

bool UFile::seek(size_t offset) {
    // Seek to a specific position in the file
    if (filePointer == nullptr) {
        // File pointer is not valid
        return false;
    }

    int result = fseek(filePointer, offset, SEEK_SET);
    return (result == 0);
}

uint32_t UFile::available() {
    // Check the available data in the file
    if (filePointer == nullptr) {
        // File pointer is not valid
        return 0;
    }

        int currentPosition = ftell(filePointer);
        fseek(filePointer, 0, SEEK_END);
        int fileSize = ftell(filePointer);
        fseek(filePointer, currentPosition, SEEK_SET);

        Arduino_UnifiedStorage::debugPrint("[File][available][INFO] Available bytes in file: " + String(fileSize - currentPosition));
        return (fileSize - currentPosition);
    }

    int UFile::read() {
        // Read a single byte from the file
        if (filePointer == nullptr) {
            // File pointer is not valid
            Arduino_UnifiedStorage::debugPrint("[File][read][ERROR] File pointer is not valid");
            return 0;
        }

        int value = fgetc(filePointer);
        return value;
    }

    size_t UFile::read(uint8_t* buffer, size_t size) {
        // Read data from the file into the buffer
        if (filePointer == nullptr) {
            // File pointer is not valid
            Arduino_UnifiedStorage::debugPrint("[File][read][ERROR] File pointer is not valid");
            return 0;
        }

        size_t bytesRead = fread(buffer, sizeof(uint8_t), size, filePointer);
        Arduino_UnifiedStorage::debugPrint("[File][read][INFO] Read " + String(bytesRead) + " bytes from file");
        return bytesRead;
    }

    String UFile::readAsString() {
        if (filePointer == nullptr) {
            Arduino_UnifiedStorage::debugPrint("[File][readAsString][ERROR] File pointer is not valid");
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

        Arduino_UnifiedStorage::debugPrint("[File][readAsString][INFO] Read string from file: " + result);
        return result;
    }

    size_t UFile::write(uint8_t value) {
        // Write a single byte to the file
        if (filePointer == nullptr) {
            // File pointer is not valid
            Arduino_UnifiedStorage::debugPrint("[File][write][ERROR] File pointer is not valid");
            return 0;
        }

        int result = fputc(value, filePointer);
        if (result == EOF) {
            Arduino_UnifiedStorage::debugPrint("[File][write][ERROR] Failed to write byte to file");
            return 0;
        }

        Arduino_UnifiedStorage::debugPrint("[File][write][INFO] Wrote 1 byte to file");
        return 1;
    }

    size_t UFile::write(String data) {
        if (filePointer == nullptr) {
            // File pointer is not valid
            Arduino_UnifiedStorage::debugPrint("[File][write][ERROR] File pointer is not valid");
            return 0;
        }

        // Write data to the file
        size_t bytesWritten = fwrite(data.c_str(), sizeof(char), data.length(), filePointer);
        Arduino_UnifiedStorage::debugPrint("[File][write][INFO] Wrote " + String(bytesWritten) + " bytes to file: " + String(path.c_str()));
                return bytesWritten;
            }

            size_t UFile::write(const uint8_t* buffer, size_t size) {
                if (filePointer == nullptr) {
                    // File pointer is not valid
                    Arduino_UnifiedStorage::debugPrint("[File][write][ERROR] File pointer is not valid: " + String(path.c_str()));
                    return 0;
                }

                size_t bytesWritten = fwrite(buffer, sizeof(uint8_t), size, filePointer);
                Arduino_UnifiedStorage::debugPrint("[File][write][INFO] Wrote " + String(bytesWritten) + " bytes to file: " + String(path.c_str()));
                return bytesWritten;
            }

            bool UFile::remove() {
                if (!this->exists() || path.empty()) {
                    return false; // Handle the case when the path is not valid
                }

                bool result = (::remove(path.c_str()) == 0);
                if (result) {
                    Arduino_UnifiedStorage::debugPrint("[File][remove][INFO] File removed successfully: " + String(path.c_str()));
                } else {
                    Arduino_UnifiedStorage::debugPrint("[File][remove][ERROR] Failed to remove file: " + String(path.c_str()));
                }

                return result;
            }

            bool UFile::rename(const char* newFilename) {
                // Rename the file
                int result = ::rename(path.c_str(), newFilename);
                if (result == 0) {
                    // Update the internal filename
                    path = newFilename;
                    Arduino_UnifiedStorage::debugPrint("[File][rename][INFO] File renamed successfully: " + String(path.c_str()));
                    return true;
                } else {
                    // Error occurred while renaming the file
                    Arduino_UnifiedStorage::debugPrint("[File][rename][ERROR] Failed to rename file: " + String(path.c_str()));
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
                    Arduino_UnifiedStorage::debugPrint("[File][exists][INFO] File exists: " + String(path.c_str()));
                    return true;
                } else {
                    // File does not exist
                    Arduino_UnifiedStorage::debugPrint("[File][exists][INFO] File does not exist: " + String(path.c_str()));
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
                    Arduino_UnifiedStorage::debugPrint("[File][copyTo][ERROR] Failed to open source file: " + String(path.c_str()));
                    return false;
                }

                FILE* destinationFile = fopen(newPath.c_str(), "r");

                if(destinationFile != nullptr){

                    if(overwrite){
                        fclose(destinationFile);
                        ::remove(newPath.c_str());
                    } else {
                        errno = EEXIST;
                        Arduino_UnifiedStorage::debugPrint("[File][copyTo][ERROR] Destination file already exists: " + String(newPath.c_str()));
                        return false;
                    }
                } 

                // Open the destination file for writing
                destinationFile = fopen(newPath.c_str(), "w");

                if (destinationFile == nullptr) {
                    fclose(sourceFile);
                    Arduino_UnifiedStorage::debugPrint("[File][copyTo][ERROR] Failed to open destination file: " + String(newPath.c_str()));
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

                Arduino_UnifiedStorage::debugPrint("[File][copyTo][INFO] File copied successfully from " + String(path.c_str()) + " to " + String(newPath.c_str()));
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

                fclose(filePointer);
                if (!copyTo(destinationPath, overwrite)) {
                    Arduino_UnifiedStorage::debugPrint("[File][moveTo][ERROR] Failed to copy file to destination: " + String(path.c_str()) + " to " + String(newPath.c_str()));
                    return false; // Return false if the copy operation fails
                }

                // Delete the source file
                if (::remove(path.c_str())) {
                    Arduino_UnifiedStorage::debugPrint("[File][moveTo][ERROR] Failed to remove source file: " + String(path.c_str()));
                    return false;
                }

                //open(newPath.c_str(), fileMode); // sure about that ?
                path = newPath;

                Arduino_UnifiedStorage::debugPrint("[File][moveTo][INFO] File moved successfully from " + String(path.c_str()) + " to " + String(newPath.c_str()));
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
