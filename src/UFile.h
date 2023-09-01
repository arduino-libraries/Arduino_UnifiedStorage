    * @brief Constructor.
    */
   */
  /**
   */
   */
   * @brief Copies the file to the specified destination path.
   * @param const char * destinationPath - The destination path to copy the file to.
   * @return True upon success, false otherwise. 
   */
   * @brief Copies the file to the specified destination path.
   * @param String destinationPath The destination path to copy the file to.
   * @return True upon success, false otherwise. 
   */
   * @brief Copies the file to the specified destination path.
   * @param Folder destinationPath - The destination folder to copy the file to.
   * @return True upon success, false otherwise. 
   */
   * @brief Moves the file to the specified destination path.
   * @param const char * destinationPath The destination path to move the file to.
   * @return True upon success, false otherwise. 
   */
   * @brief Moves the file to the specified destination path.
   * @param String destinationPath The destination path to move the file to.
   * @return True upon success, false otherwise. 
   */
   * @brief Copies the file to the specified destination folder.
   * @param Folder destinationFolder The destination directory to move the file to.
   * @return True upon success, false otherwise. 
   */
  /**
   * @brief Returns a reference to the parent folder of the current folder. 
   * @return A directory object representing the current folder. 
   */
  /**
   * @brief Returns the path of the directory.
   * @return The path of the file as a const char * 
   */
  /**
   * @brief Returns the path of the directory.
   * @return The path of the file as a String
   */

  /**
   * @brief Returns the number of bytes available to read
   * @return The number of bytes available to read as int
   */
  int available();

  /**
   * @brief Returns one byte from the file 
   * @return An int representing one byte from the file
   */
  int read();

  /**
   * @brief Writes one byte to the file
   * @param a uint8_t value representing the byte to write
   */