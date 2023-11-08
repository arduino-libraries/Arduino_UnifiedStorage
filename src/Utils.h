#ifndef Utils_H
#define Utils_H
#define PATH_MAX_LENGTH 255

#include "Arduino.h"
#include "Arduino_UnifiedStorage.h"
#include "Arduino_POSIXStorage.h"
#include <iostream>

#if !defined(HAS_SERIAL) && defined(HAS_RS485)
#include <ArduinoRS485.h>


[[gnu::unused]] static void beginRS485(const int baudrate){
    const auto bitduration { 1.f / baudrate };
    const auto wordlen { 9.6f }; // OR 10.0f depending on the channel configuration
    const auto preDelayBR { bitduration * wordlen * 3.5f * 1e6 };
    const auto postDelayBR { bitduration * wordlen * 3.5f * 1e6 };

    RS485.begin(baudrate);
    RS485.setDelays(preDelayBR, postDelayBR);
    RS485.noReceive();
}

[[gnu::unused]] static void debugPrintRS485(String s){
    static bool rs485Initialized = false;
    if (!rs485Initialized) {
      beginRS485(115200);
      rs485Initialized = true;
    }
    RS485.beginTransmission();
    RS485.write(s.c_str(), strlen(s.c_str()));
    RS485.write('\n');
    RS485.endTransmission();
}

#endif


[[gnu::unused]] static String prettyPrintFileSystemType(FileSystems f){
    if(f == 0) return "FAT";
    else if(f == 1) return "LitlleFS";
    else return "";
}


[[gnu::unused]] static const char* createPartitionName(int number) {
    // check if the number can be represented by a letter of the alphabet
    if (number < 1 || number > 26) {
        // Handle out-of-range numbers or errors as needed
        return nullptr;
    }

    char partitionName[13]; // "partition_" + letter + '\0'
    snprintf(partitionName, sizeof(partitionName), "%c", 'a' + number - 1);

    // Dynamically allocate memory for the string and copy the generated value
    char* dynamicName = new char[strlen(partitionName) + 1];
    strcpy(dynamicName, partitionName);

    return dynamicName;
}


[[gnu::unused]] static bool copyFolder(const char* source, const char* destination) {
  DIR* dir = opendir(source);
  if (dir == nullptr) {
    printf("Failed to open source directory\n");
    return false;
  }

  // Create destination directory if it doesn't exist
  if (mkdir(destination, 0777) != 0 && errno != EEXIST) {
    printf("Failed to create destination directory\n");
    closedir(dir);
    return false;
  }

  struct dirent* entry;
  while ((entry = readdir(dir)) != nullptr) {
    // Skip "." and ".."
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }


    size_t sourcePathLength = strlen(source) + strlen(entry->d_name) + 1;
    size_t destinationPathLength = strlen(destination) + strlen(entry->d_name) + 1;

    char* sourcePath = new char[sourcePathLength];
    char* destinationPath = new char[destinationPathLength];

    snprintf(sourcePath, sourcePathLength, "%s/%s", source, entry->d_name);

    snprintf(destinationPath, destinationPathLength, "%s/%s", destination, entry->d_name);

    struct stat fileInfo;
    if (stat(sourcePath, &fileInfo) != 0) {
      closedir(dir);
      delete(sourcePath);
      delete(destinationPath);
      return false;
    }

    if (S_ISDIR(fileInfo.st_mode)) {
      // Recursively copy subdirectories
      if (!copyFolder(sourcePath, destinationPath)) {
        closedir(dir);
        delete(sourcePath);
        delete(destinationPath);
        return false;
      }
    } else {
      // Copy regular files
      FILE* sourceFile = fopen(sourcePath, "r");
      if (sourceFile == nullptr) {
        closedir(dir);
        delete(sourcePath);
        delete(destinationPath);
        return false;
      }

      FILE* destinationFile = fopen(destinationPath, "w");
      if (destinationFile == nullptr) {
        fclose(sourceFile);
        closedir(dir);
        delete(sourcePath);
        delete(destinationPath);
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

  closedir(dir);
  return true;
}

[[gnu::unused]] static std::string replaceLastPathComponent(const std::string& path, const std::string& newComponent) {
    size_t lastSlashIndex = path.find_last_of('/');
    if (lastSlashIndex != std::string::npos) {
        std::string newPath = path.substr(0, lastSlashIndex + 1) + newComponent;
        return newPath;
    }
    return path;
}

// Helper function to get the last path component
[[gnu::unused]] static std::string getLastPathComponent(const std::string& path) {
    size_t lastSlashIndex = path.find_last_of('/');
    if (lastSlashIndex != std::string::npos) {
        return path.substr(lastSlashIndex + 1);
    }
    return path;
}

// Helper function to replace the first path component with a new component
[[gnu::unused]] static std::string replaceFirstPathComponent(const std::string& path, const std::string& destinationPath) {
    std::string fileName = getLastPathComponent(path);
    std::string newPath = destinationPath + "/" + fileName;
    return newPath;
}

 inline static String getErrno(){
  switch (errno) {
    case ENOENT:
      return "No such file or directory";
    case EEXIST:
      return "File or directory already exists";
    case EIO:
      return "Input/output error";
    case ENOTDIR:
      return "Not a directory";
    case EISDIR:
      return "Is a directory";
    case ENFILE:
      return "Too many open files in system";
    case EMFILE:
      return "Too many open files";
    case ENOSPC:
      return "No space left on device";
    case ENAMETOOLONG:
      return "File name too long";
    case EPERM:
      return "Operation not permitted";
    case ENODEV:
      return "No such device";
    case ENOTBLK:
      return "Not a block device";
    case EBUSY:
      return "Device or resource busy";
    case EAGAIN:
      return "Resource temporarily unavailable";
    case ENXIO:
      return "No such device or address";
    case ENOMEM:
      return "Out of memory";
    case EACCES:
      return "Permission denied";
    case EROFS:
      return "Read-only file system";
    case EINVAL:
      return "Invalid argument";
    default:
      return "Undefined Error";
    }
}



#endif 
