

### Use QSPI Flash, SD cards, and USB mass storage devices
This library allows you to easily switch between different storage mediums on supported boards, check the "Compatibility" section for more details about what storage medium is supported on what board. 

To initialise the storage medium you need to create a `UnifiedStorage` object, and to mount it you need to call it's `begin()` method:

```c
UnifiedStorage storageMedium = USBStorage(); // or
// UnifiedStorage sd = SDStorage();
// UnifiedStorage internal = InternalStorage();

void setup(){
	storageMedium.begin();
}
```
You can initialize a UnifiedStorage object of each type (QSPI, SD, USB), and copy files and folders from one medium to another.
 
### Open, Write, and Read Files
 
#### Creating / Opening / Closing Files

You can create or open a file by providing a reference to the root folder of the storage medium or by specifying the full absolute path.

```cpp
Folder root = storageMedium.getRootFolder();
UFile document = root.createFile("file.txt", FileMode::READ);
```

```cpp
UFile document = UFile();
document.open("<absolute_path>/file.txt", FileMode::READ);
```

You can change the mode of an opened file using the `changeMode()` method.

```cpp
document.changeMode(FileMode::WRITE);
```

#### Reading and Writing Files

You can read data from a file using the `read()` method and write data to a file using the `write()` method.

```cpp
uint8_t buffer[128];
size_t bytesRead = document.read(buffer, sizeof(buffer));
```

```cpp
String data = "Hello, World!";
char buffer[data.length() + 1];
data.toCharArray(buffer, sizeof(buffer));
size_t bytesWritten = document.write(reinterpret_cast<const uint8_t*>(buffer), data.length());
```

Alternatively, you can read and write files using strings.

```cpp
String content = document.readAsString();
```

```cpp
String data = "Hello, World!";
size_t bytesWritten = document.write(data);
```

### File Seeking and Availability

The `seek()` and `available()` methods provide functionality for file seeking and checking the available data in a file. Here's an overview of how to use these methods:

#### Seek to a Specific Position in the File

The `seek()` method allows you to move the file pointer to a specific position in the file. It takes an offset parameter, which represents the number of bytes to move from a reference position. Here's an example:

```cpp
// Seek to the 10th byte in the file
bool success = file.seek(10);
if (success) {
  // File pointer is now at the desired position
} else {
  // Seek operation failed
}
```

In this example, the `seek()` method is called with an offset of 10, which moves the file pointer to the 10th byte in the file. The method returns a boolean value indicating the success of the seek operation.

#### Check Available Data in the File

The `available()` method returns the number of bytes available for reading from the current file position. It can be used to determine how much data is left to be read in the file. Here's an example:

```cpp
// Check the available data in the file
int availableBytes = file.available();
if (availableBytes > 0) {
  // There is data available to be read
} else {
  // No more data available
}
```

In this example, the `available()` method is called to retrieve the number of available bytes in the file. If the value is greater than 0, it means there is data available to be read. Otherwise, there is no more data left in the file.

These methods are useful for scenarios where you need to navigate to a specific position in a file or check the availability of data before performing read operations.

### File Manipulation
The library provides various file manipulation operations such as renaming, deleting, moving, and copying files.

#### Renaming a File

You can rename an existing file using the `rename()` method.

```cpp
bool success = document.rename("newfile.txt");
```

#### Deleting a File

You can delete a file using the `remove()` method.

```cpp
bool success = document.remove();
```

#### Moving a File

You can move a file to a different directory using the `moveTo()` method.

```cpp
Folder destination = storageMedium.getRootFolder().createSubfolder("destination");
bool success = document.moveTo(destination);
```

#### Copying a File

You can copy a file to a different directory using the `copyTo()` method.

```cpp
Folder destination = storageMedium.getRootFolder().createSubfolder("destination");
bool success = document.copyTo(destination);
```

### Folder Manipulation
The library provides methods to create, rename, delete, move, copy, and list directories.

#### Creating a Folder

You can create a new directory using the `createSubfolder()` method.

```cpp
Folder root = storageMedium.getRootFolder();
Folder newFolder = root.createSubfolder("new_folder");
```

#### Renaming a Folder

You can rename an existing directory using the `rename()` method.

```cpp
bool success = newFolder.rename("renamed_folder");
```

#### Deleting a Folder

You can delete a directory using the `remove()` method.

```cpp
bool success = newFolder.remove();
```

#### Moving a Folder

You can move a directory to a different location using the `moveTo()` method.

```cpp
Folder destination = storageMedium.getRootFolder().createSubfolder("destination");
bool success = newFolder.moveTo(destination);
```

#### Copying a Folder

You can copy a directory to a different location using the `copyTo()` method.

```cpp
Folder destination = storageMedium.getRootFolder().createSubfolder("destination");
bool success = newFolder.copyTo(destination);
```

#### Listing Files and Directories

You can get a list of files and directories in a directory using the `getFiles()` and `getFolders()` methods.

```cpp
std::vector<UFile> files = root.getFiles();
std::vector<Folder> folders = root.getFolders();
```

#### Traversing Files and Directories

You can traverse through all the files and directories in a directory using a loop and the `getFiles()` and `getFolders()` methods.

```cpp
std::vector<UFile> files = root.getFiles();
for ( UFile file : files) {
    // Perform operations on each file
}

std::vector<Folder> folders = root.getFolders();
for (Folder folder : folders) {
    // Perform operations on each folder
}
```