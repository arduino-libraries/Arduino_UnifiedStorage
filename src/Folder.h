#ifndef Folder_H
#define Folder_H

#include "Arduino_UnifiedStorage.h"
#include "Utils.h"
#include "UFile.h"
#include <vector>

class UFile;
/**
 * @class Folder
 * @brief Class representing a directory.
 */
class Folder {

  public:
    /**
     * @brief Creates an empty Folder object. 
     * Please note that any operation on this object will fail until a valid directory is assigned to it.
     */
    Folder();

    /**
     * @brief Creates a directory with the specified name.
     * If the directory already exists, it returns a Folder object representing the existing directory.
     * Otherwise, it tries to create a new directory with the specified name. If it fails the `path` property of the Folder object will be null.
     * @param const char * dirname - The name of the directory.
     */
    Folder(const char * dirname);

    /**
     * @brief Creates a directory with the specified name.
     * If the directory already exists, it returns a Folder object representing the existing directory.
     * Otherwise, it tries to create a new directory with the specified name. If it fails the `path` property of the Folder object will be empty.
     * @param String dirname - The name of the directory.
     */
    Folder(String dirname);

    /**
     * @brief Creates a file inside the directory.
     * @param const char * fileName - The name of the file to create.
     * @return A File object if successful, NULL if not. 
     */
    UFile createFile(const char * fileName, FileMode fmode);

    /**
     * @brief Creates a file inside the directory.
     * @param String fileName - The name of the file to create.
     * @return A File object if successful, NULL if not. 
     */
    UFile createFile(String fileName, FileMode fmode);

    /**
     * @brief Removes a directory.
     * @param dirname The name of the directory to remove.
     * @return True if the directory was removed successfully, false otherwise.
     */
    bool remove();

    /**
     * @brief Renames a directory.
     * @param const char * newDirname The new name of the directory.
     * @return True if the directory was renamed successfully, false otherwise.
     */
    bool rename(const char * newDirname);

    /**
     * @brief Renames a directory.
     * @param String newDirname The new name of the directory.
     * @return True if the directory was renamed successfully, false otherwise.
     */
    bool rename(String newDirname);

    /**
     * @brief Checks if the directory exists.
     * @return True if the directory exists, false otherwise.
     */
    bool exists();

    /**
     * @brief Returns the path of the file.
     * @return The path of the file as a const char * 
     */
    const char * getPath();

    /**
     * @brief Returns the path of the file.
     * @return The path of the file as an Arduino String
    */
    String getPathAsString();

    /**
     * @brief Creates a subfolder in the directory.
     * @param const char * subfolderName - he name of the subfolder to create.
     * @param overwrite - behaviour in case the folder already exists, default is false
     * @return The created subfolder.
    */
    Folder createSubfolder(const char * subfolderName, bool overwrite = false);

    /**
     * @brief Creates a subfolder in the directory.
     * @param String subfolderName - he name of the subfolder to create.
     * @param overwrite - behaviour in case the folder already exists, default is false
     * @return The created subfolder.
     */
    Folder createSubfolder(String subfolderName, bool overwrite = false);

    /**
     * @brief Returns File objects for all files in the current directory.
     * @return A std::vector of File objects representing the files in the directory.
     */
    std::vector<UFile> getFiles();

    /**
     * @brief Returns Folder objects for all files in the current directory.
     * @return A std::vector of Folder objects representing the files in the directory.
     */
    std::vector<Folder>  getFolders();

    /**
     * @brief Copies the current directory
     * @param Folder destination - a Folder object representing the destination
     * @return True upon success, false otherwise. 
     */
    bool copyTo(Folder destination, bool overwrite = false);

    /**
     * @brief Copies the current directory
     * @param const char * destination - the path of the destination location
     * @param overwrite - behaviour in case the folder already exists, default is false
     * @return True upon success, false otherwise. 
     */
    bool copyTo(const char * destination, bool overwrite = false);

    /**
     * @brief Copies the current directory
     * @param String destination - the path of the destination location
     * @param overwrite - behaviour in case the folder already exists, default is false
     * @return True upon success, false otherwise. 
     */
    bool copyTo(String destination, bool overwrite = false);

    /**
     * @brief Moves the current directory
     * @param Folder destination - a Folder object representing the destination
     * @param overwrite - behaviour in case the folder already exists, default is false
     * @return True upon success, false otherwise. 
     */
    bool moveTo(Folder destination, bool overwrite = false);

    /**
     * @brief Moves the current directory
     * @param const char * destination - the path of the destination location
     * @param overwrite - behaviour in case the folder already exists, default is false
     * @return True upon success, false otherwise. 
    */
    bool moveTo(const char * destination, bool overwrite = false);

    /**
     * @brief Move the current directory
     * @param String destination - the path of the destination location
     * @param overwrite - behaviour in case the folder already exists, default is false
     * @return True upon success, false otherwise. 
     */
    bool moveTo(String destination, bool overwrite = false);

  private: 
    std::string path;
};

#endif