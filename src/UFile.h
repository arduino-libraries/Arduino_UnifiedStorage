#ifndef File_H
#define File_H

#include <Arduino.h>
#include "Arduino_UnifiedStorage.h"
#include <string.h>
#include <vector>
#include "Utils.h"

class Folder;
#include "Folder.h"

/**
 * Class representing a File
 */
class UFile{
public:

  /**
    * @brief Constructor.
    */
  UFile();

  /**
   * @brief Constructor.
   * @param const char * path - path of the file
   */
  UFile(const char* path);

  ~UFile();

  /**
   * @brief Closes the file, and opens it again with a new file mode
   * @param mode The file mode (READ, WRITE, or APPEND).
   * @return True if operation was successful, false otherwise.
   */
  bool changeMode(FileMode mode);

  /**
   * @brief Opens a file with the specified mode.
   * @param const char * filename - The name of the file to open.
   * @param mode The file mode (READ, WRITE, or APPEND).
   * @return True if the file was opened successfully, false otherwise.
   */
  bool open(const char* filename, FileMode mode);

  /**
   * @brief Opens a file with the specified mode.
   * @param String filename - The name of the file to open.
   * @param mode The file mode (READ, WRITE, or APPEND).
   * @return True if the file was opened successfully, false otherwise.
   */
  bool open(String filename, FileMode mode);


  /**
   * @brief Closes the file and releases any allocated resources.
   */
  void close();

  /**
   * @brief Seeks to a specific position in the file.
   * @param offset The offset from the beginning of the file.
   * @return True if the seek operation was successful, false otherwise.
   */
  bool seek(size_t offset);

  /**
   * @brief Reads data from the file into a buffer.
   * @param buffer The buffer to read data into.
   * @param size The size of the buffer.
   * @return The number of bytes read from the file.
   */
  size_t read(uint8_t* buffer, size_t size);

  /**
   * @brief Reads the contents of the file as an Arduino String.
   * @return The file contents as a String.
   */
  String readAsString();

  /**
   * @brief Writes data to the file from a buffer.
   * @param buffer The buffer containing the data to write.
   * @param size The size of the data to write.
   * @return The number of bytes written to the file.
   */
  size_t write(const uint8_t* buffer, size_t size);

  /**
   * @brief Writes a string to the file.
   * @param data The string to write.
   * @return The number of bytes written to the file.
   */
  size_t write(String);

  /**
   * @brief Removes the file.
   * @return True if the file was removed successfully, false otherwise.
   */
  bool remove();

  /**
   * @brief Renames the file.
   * @param const char * newFilename The new name of the file.
   * @return True if the file was renamed successfully, false otherwise.
   */
  bool rename(const char* newFilename);

  /**
   * @brief Renames the file.
   * @param String newFilename The new name of the file.
   * @return True if the file was renamed successfully, false otherwise.
   */
  bool rename(String newFilename);

  /**
   * @brief Checks if the file exists.
   * @return True if the file exists, false otherwise.
   */
  bool exists();

  /**
   * @brief Copies the file to the specified destination path.
   * @param const char * destinationPath - The destination path to copy the file to.
   * @return True upon success, false otherwise. 
   */
  bool copyTo(const char* destinationPath, bool overwrite = false);

  /**
   * @brief Copies the file to the specified destination path.
   * @param String destinationPath The destination path to copy the file to.
   * @return True upon success, false otherwise. 
   */
  bool copyTo(String destinationPath, bool overwrite = false);

  /**
   * @brief Copies the file to the specified destination path.
   * @param Folder destinationPath - The destination folder to copy the file to.
   * @return True upon success, false otherwise. 
   */
  bool copyTo(Folder destinationFolder, bool overwrite = false);

  /**
   * @brief Moves the file to the specified destination path.
   * @param const char * destinationPath The destination path to move the file to.
   * @return True upon success, false otherwise. 
   */
  bool moveTo(const char * destinationPath, bool overwrite = false);

  /**
   * @brief Moves the file to the specified destination path.
   * @param String destinationPath The destination path to move the file to.
   * @return True upon success, false otherwise. 
   */
  bool moveTo(String destinationPath, bool overwrite = false);

  /**
   * @brief Copies the file to the specified destination folder.
   * @param Folder destinationFolder The destination directory to move the file to.
   * @return True upon success, false otherwise. 
   */
  bool moveTo(Folder  destinationFolder, bool overwrite = false);

  /**
   * @brief Returns a reference to the parent folder of the current folder. 
   * @return A directory object representing the current folder. 
   */
  Folder getParentFolder();

  /**
   * @brief Returns the path of the directory.
   * @return The path of the file as a const char * 
   */
  const char * getPath();

  /**
   * @brief Returns the path of the directory.
   * @return The path of the file as a String
   */
  String getPathAsString();

  /**
   * @brief Returns the number of bytes available to read
   * @return The number of bytes available to read as int
   */
  uint32_t available();

  /**
   * @brief Returns one byte from the file 
   * @return An int representing one byte from the file
   */
  int read();

  /**
   * @brief Writes one byte to the file
   * @param a uint8_t value representing the byte to write
   */
  size_t write(uint8_t value);


private:
  FILE* filePointer;
  uint8_t* readBuffer;
  std::string path;
  FileMode fileMode;
};

#endif