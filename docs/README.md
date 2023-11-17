
  
  

### Use QSPI Flash, SD cards, and USB mass storage devices

This library allows you to easily switch between different storage mediums on supported boards, check the "Compatibility" section for more details about what storage medium is supported on what board.

To initialise the storage medium you need to create a `Arduino_UnifiedStorage` object, and to mount it you need to call it's `begin()` method:

 
```c

Arduino_UnifiedStorage storageMedium =  USBStorage(); // or

// Arduino_UnifiedStorage sd = SDStorage();

// Arduino_UnifiedStorage internal = InternalStorage();

 
void  setup(){
	storageMedium.begin();
}

```

There is also an overloaded version of the `begin()` method that takes in an argument of type `FileSystems` (can be `FS_FAT` or `FS_LITTLEFS`)

```

void setup(){
	storageMedium.begin(FS_FAT);
}
```

#### Automatic partition and filesystem detection for InternalStorage
In the case of InternalStorage, a board might not come pre-partitioned when it leaves the factory, therefore, the default constructor for InternalStorage does the following steps.
* Checks if there are any partitions on the drive.
	* If there are no partitions it creates the default partitioning scheme (see the **Read and create partitions on the Internal (QSPI) Storage** section for more information)
* Selects the last partition, detects the file-system type automatically and mounts it 

### Format QSPI Flash, SD cards, and USB mass storage devices

This library also allows you to format any partition or drive to either FAT or LittleFS filesystems.

  

```storageMedium.format(FS_FAT)```

or

```storageMedium.format(FS_LITTLEFS);```

  

Please make sure you call format before calling `begin()` or after calling `unmount()`.

  

### Open, Write, and Read Files

#### Creating / Opening / Closing Files

  

You can create or open a file by providing a reference to the root folder of the storage medium or by specifying the full absolute path.

  

```cpp

Folder root =  storageMedium.getRootFolder();

UFile document =  root.createFile("file.txt", FileMode::READ);

```

  

```cpp

UFile document =  UFile();

document.open("<absolute_path>/file.txt", FileMode::READ);

```

  

You can change the mode of an opened file using the `changeMode()` method.

  

```cpp

document.changeMode(FileMode::WRITE);

```

  

#### Reading and Writing Files

  

You can read data from a file using the `read()` method and write data to a file using the `write()` method.

  

```cpp

uint8_t  buffer[128];

size_t bytesRead =  document.read(buffer, sizeof(buffer));

```

  

```cpp

String data =  "Hello, World!";

char  buffer[data.length() +  1];

data.toCharArray(buffer, sizeof(buffer));

size_t bytesWritten =  document.write(reinterpret_cast<const  uint8_t*>(buffer), data.length());

```

  

Alternatively, you can read and write files using strings.

  

```cpp

String content =  document.readAsString();

```

  

```cpp

String data =  "Hello, World!";

size_t bytesWritten =  document.write(data);

```

  

### File Seeking and Availability

  

The `seek()` and `available()` methods provide functionality for file seeking and checking the available data in a file. Here's an overview of how to use these methods:

  

#### Seek to a Specific Position in the File

  

The `seek()` method allows you to move the file pointer to a specific position in the file. It takes an offset parameter, which represents the number of bytes to move from a reference position. Here's an example:

  

```cpp

// Seek to the 10th byte in the file

bool success =  file.seek(10);

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

int availableBytes =  file.available();

if (availableBytes >  0) {

// There is data available to be read

} else {

// No more data available

}

```

  

In this example, the `available()` method is called to retrieve the number of available bytes in the file. If the value is greater than 0, it means there is data available to be read. Otherwise, there is no more data left in the file.

  

These methods are useful for scenarios where you need to navigate to a specific position in a file or check the availability of data before performing read operations.

  

### Close files

Closing files is extremely important as filesystems might fail to unmount if files are kept open. You can close files by calling `file.close()`

  

### File Manipulation

The library provides various file manipulation operations such as renaming, deleting, moving, and copying files.

  

#### Renaming a File

  

You can rename an existing file using the `rename()` method.

  

```cpp

bool success =  document.rename("newfile.txt");

```

  

#### Deleting a File

  

You can delete a file using the `remove()` method.

  

```cpp

bool success =  document.remove();

```

  

#### Moving a File

  

You can move a file to a different directory using the `moveTo()` method.

  

```cpp

Folder destination =  storageMedium.getRootFolder().createSubfolder("destination");

bool success =  document.moveTo(destination);

```

  

This method also allows you to set the behaviour if there's an existing file with the same name at the location you want to move to. You can set the optional parameter `overwrite` to `true`.

```cpp

bool success =  document.moveTo(destination, true);

```

  
  

Please note that the `File`` object will point now to the moved file, not the original one.

#### Copying a File

  

You can copy a file to a different directory using the `copyTo()` method.

  

```cpp

Folder destination =  storageMedium.getRootFolder().createSubfolder("destination");

bool success =  document.copyTo(destination);

```

  

This method also allows you to set the behaviour if there's an existing file with the same name at the location you want to move to. You can set the optional parameter `overwrite` to `true`.

```cpp

bool success =  document.copyTo(destination, true);

```

  

Please note that the `UFile` object will point now to the copy of the file, not the original one.

  

### Folder Manipulation

The library provides methods to create, rename, delete, move, copy, and list directories.

  

#### Creating a Folder

  

You can create a new directory using the `createSubfolder()` method.

  

```cpp

Folder root =  storageMedium.getRootFolder();

Folder newFolder =  root.createSubfolder("new_folder");

```

  

#### Renaming a Folder

  

You can rename an existing directory using the `rename()` method.

  

```cpp

bool success =  newFolder.rename("renamed_folder");

```

  

#### Deleting a Folder

  

You can delete a directory using the `remove()` method.

  

```cpp

bool success =  newFolder.remove();

```

  

#### Moving a Folder

  

You can move a directory to a different location using the `moveTo()` method.

  

```cpp

Folder destination =  storageMedium.getRootFolder().createSubfolder("destination");

bool success =  newFolder.moveTo(destination);

```

This method also allows you to set the behaviour if there's an existing Folder with the same name at the location you want to move to. You can set the optional parameter `overwrite` to `true`.

```cpp

bool success =  newFolder.moveTo(destination, true);

```

  

Please note that the `Folder`` object will point now to the moved folder.

  
  

#### Copying a Folder

  

You can copy a directory to a different location using the `copyTo()` method.

  

```cpp

Folder destination =  storageMedium.getRootFolder().createSubfolder("destination");

bool success =  newFolder.copyTo(destination);

```

  

This method also allows you to set the behaviour if there's an existing Folder with the same name at the location you want to move to. You can set the optional parameter `overwrite` to `true`.

```cpp

bool success =  newFolder.copyTo(destination, true);

```

  

Please note that the `Folder`` object will point now to the copy of the folder, not the original one.

  
  

#### Listing Files and Directories

  

You can get a list of files and directories in a directory using the `getFiles()` and `getFolders()` methods.

  

```cpp

std::vector<UFile> files =  root.getFiles();

std::vector<Folder> folders =  root.getFolders();

```

  

#### Traversing Files and Directories

  

You can traverse through all the files and directories in a directory using a loop and the `getFiles()` and `getFolders()` methods.

  

```cpp

std::vector<UFile> files =  root.getFiles();

for ( UFile file : files) {

// Perform operations on each file

}

  

std::vector<Folder> folders =  root.getFolders();

for (Folder folder : folders) {

// Perform operations on each folder

}

```
### Register connection and disconnection callbacks for USB drives
In the case of removable storage, such as USB mass storage devices, it's particularly useful to be able to know when a drive has been connected and disconnected and perform specific actions in those situations. 

This library allows you to register and unregister connection and disconnection callbacks. Check out this example on how to do that: 

```c
USBStorage usbThumbDrive;

void connectionCallbackMethod(){
	connected = true;
}

void disconnectedCallbackMethod(){
	connected = false;
}

void setup(){
	usbThumbDrive = USBStorage();
	usbThumbDrive.onConnect(connectionCallbackMethod);
	usbThumbDrive.onDisconnect(disconnectedCallbackMethod);
	
	// to unregister these callbacks use the following methods:
	// usbThumbDrive.removeOnConnectCallback();
	// usbThumbDrive.removeOnDisconnectCallback(); 
}

```

### Read and create partitions on the Internal (QSPI) Storage
Partitioning internal storage in embedded devices offers benefits such as improved data organization, security, and error recovery. It facilitates easier management, isolates critical components, enables safer firmware updates, and enhances overall system resilience. Additionally, it reduces wear and tear of the flash chip. We recommend using the LittleFS file-system whenever possible on the partition you write to the most as it is designed specifically to reduce wear and tear. 

To partition the internal storage using the Arduino_UnifiedStorage library, you need to create a std::vector of `Partition` you'd like to write to the drive. 
```c
std::vector<Partition> partitioningScheme = {
	{1024, FS_FAT}, // 1 MB for certificates
	{5120, FS_FAT}, // 5 MB for OTA firmware updates
	{8192, FS_LITTLEFS} // 8 MB for user data
})
```
`Partition` is a struct that contains the size of a partition and the file-system it should be formatted as. `fileSystemType` can be either `FS_FAT` or `FS_LITTLEFS`
```c
struct Partition {
	int  size;
	FileSystems fileSystemType;
};
```

The partitioning schemes should follow a few strict guidelines, failure to comply with these might result in a hard-fault, and on the Portenta H7 and Opta you might see a blinking red LED:
1. MBR supports up to 4 partitions, please do not add more than that
2. Partitions should be of a sensible size (at least 16 bytes to fit a MBR partition header)
3. Partition size must be aligned with the block size (usually 4096 bytes)
4. Partition size must not be larger than the available storage space (16MB Portenta, Opta, Nicla Vision boards)

To write a partition scheme to the drive, you can use the `InternalStorage::partition` method with a std:vector of `Partition` as a parameter. 

You can also read the existing partitioning table using `InternalStorage::readPartitions`. This will return a vector of `Partition`. In case there are no partitions on the drive, it will return an empty vector.  

Check out the `InternalStoragePartitioning` example for more info. 

### Enable debugging output
In some cases it might be useful to know what's happening under the hood. If you would like to get more a verbose output on either Serial or RS485 you can add the following to your sketch before initializing any of the library related objects.
 
`Arduino_UnifiedStorage::debuggingModeEnabled  =  true;`
 
