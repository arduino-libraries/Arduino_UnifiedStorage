# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`Arduino_UnifiedStorage`](#class_arduino___unified_storage) | Abstract class representing the common features of the supported storage methods
`class ` [`Folder`](#class_folder) | Class representing a directory.
`class ` [`InternalStorage`](#class_internal_storage) | Represents internal storage using the Arduino Unified Storage library.
`class ` [`Partitioning`](#class_partitioning) | 
`class ` [`SDStorage`](#class_s_d_storage) | Represents an SD card storage using the Arduino Unified Storage library.
`class ` [`UFile`](#class_u_file) | Class representing a File
`class ` [`USBStorage`](#class_u_s_b_storage) | [USBStorage](#class_u_s_b_storage) class provides an interface to access USB storage devices. It inherits from the [Arduino_UnifiedStorage](#class_arduino___unified_storage) class and implements its pure virtual functions.
`struct ` [`Partition`](#struct_partition) | 

# class `Arduino_UnifiedStorage` <a id="class_arduino___unified_storage" class="anchor"></a>

Abstract class representing the common features of the supported storage methods

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`begin`](#class_arduino___unified_storage_1a350443027c76ea18f2812a54aa8ab437) | Initializes the storage. |
| [`begin`](#class_arduino___unified_storage_1acb25f75f3dcdb89ebce3c7cd08970a99) | Initializes the storage with the specified file system.  |
| [`unmount`](#class_arduino___unified_storage_1a4281bc190ee4f2ad35265eab64ef6f7f) | Unmounts the storage.  |
| [`getRootFolder`](#class_arduino___unified_storage_1a7166075ba695d54bf74c6c71b8c4c1bf) | Retrieves the root folder of the storage.  |
| [`format`](#class_arduino___unified_storage_1ad6d045b4bdafd4dcb75daed305888e25) | Formats the storage with the selected file system.  |
| [`debugPrint`](#class_arduino___unified_storage_1a466b794918c895d105501507f9337e61) |  |
| [`testPrint`](#class_arduino___unified_storage_1ab76317acb2bf69c6fdf7575ed317e8f2) |  |

## Members

### `begin` <a id="class_arduino___unified_storage_1a350443027c76ea18f2812a54aa8ab437" class="anchor"></a>

```cpp
public bool begin()
```

Initializes the storage.

#### Returns
true if successful, false if failed.
<hr />

### `begin` <a id="class_arduino___unified_storage_1acb25f75f3dcdb89ebce3c7cd08970a99" class="anchor"></a>

```cpp
public bool begin(FileSystems fs)
```

Initializes the storage with the specified file system. 
#### Parameters
* `fs` The desired file system (FS_FAT or FS_LITTLEFS). 

#### Returns
true if successful, false if failed.
<hr />

### `unmount` <a id="class_arduino___unified_storage_1a4281bc190ee4f2ad35265eab64ef6f7f" class="anchor"></a>

```cpp
public bool unmount()
```

Unmounts the storage. 
#### Returns
true if successful, false if failed.
<hr />

### `getRootFolder` <a id="class_arduino___unified_storage_1a7166075ba695d54bf74c6c71b8c4c1bf" class="anchor"></a>

```cpp
public Folder getRootFolder()
```

Retrieves the root folder of the storage. 
#### Returns
The root folder as a [Folder](#class_folder) object.
<hr />

### `format` <a id="class_arduino___unified_storage_1ad6d045b4bdafd4dcb75daed305888e25" class="anchor"></a>

```cpp
public bool format(FileSystems fs)
```

Formats the storage with the selected file system. 
#### Returns
true if successful, false if failed.
<hr />

### `debugPrint` <a id="class_arduino___unified_storage_1a466b794918c895d105501507f9337e61" class="anchor"></a>

```cpp
public static void debugPrint(String message)
```

<hr />

### `testPrint` <a id="class_arduino___unified_storage_1ab76317acb2bf69c6fdf7575ed317e8f2" class="anchor"></a>

```cpp
public static void testPrint(String message)
```

<hr />

# class `Folder` <a id="class_folder" class="anchor"></a>

Class representing a directory.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Folder`](#class_folder_1a8af69fd19ba86816c60b4c2291311eb1) | Creates an empty [Folder](#class_folder) object. Please note that any operation on this object will fail until a valid directory is assigned to it. |
| [`Folder`](#class_folder_1aa2a4dc98e8c383c7b4fa503b45813fe3) | Creates a directory with the specified name. If the directory already exists, it returns a [Folder](#class_folder) object representing the existing directory. Otherwise, it tries to create a new directory with the specified name. If it fails the `path` property of the [Folder](#class_folder) object will be null. |
| [`Folder`](#class_folder_1a6f445bfe0214a03ba00a1408e41726dd) | Creates a directory with the specified name. If the directory already exists, it returns a [Folder](#class_folder) object representing the existing directory. Otherwise, it tries to create a new directory with the specified name. If it fails the `path` property of the [Folder](#class_folder) object will be empty. |
| [`createFile`](#class_folder_1a04eceb0406b02e2d8a628d3c359dba5d) | Creates a file inside the directory. |
| [`createFile`](#class_folder_1a44255e2c0c4ffa37d7637a601bc590f6) | Creates a file inside the directory. |
| [`remove`](#class_folder_1aca893daac6c6747895d50987cf9cf34c) | Removes a directory. |
| [`rename`](#class_folder_1adcbb7766d628810f716887d1e7e8d36f) | Renames a directory. |
| [`rename`](#class_folder_1a14519c2a344ebfb8161c2bee2a2b5464) | Renames a directory. |
| [`exists`](#class_folder_1aa548278d3ec09fd4abcaa827a79c40f4) | Checks if the directory exists. |
| [`getPath`](#class_folder_1a0ef68289c526f8bf24020389c4e09e86) | Returns the path of the file. |
| [`getPathAsString`](#class_folder_1ac816d0fe5674c4648e97423b6f9c51f8) | Returns the path of the file. |
| [`createSubfolder`](#class_folder_1a78f2f9b297f62b67c2e0656b15a95868) | Creates a subfolder in the directory. |
| [`createSubfolder`](#class_folder_1ab50743664becb7b2a1fb564b5513d69c) | Creates a subfolder in the directory. |
| [`getFiles`](#class_folder_1a2e7f604d19b8ad61524f86ade86ed4ad) | Returns File objects for all files in the current directory. |
| [`getFolders`](#class_folder_1a5554b8cc2fd1ca39dfccbd06bc635e10) | Returns [Folder](#class_folder) objects for all files in the current directory. |
| [`copyTo`](#class_folder_1aabf0818b7ee45b2d871e82e86edb4ebd) | Copies the current directory. |
| [`copyTo`](#class_folder_1a058d193f53c559eefe343b30797500eb) | Copies the current directory. |
| [`copyTo`](#class_folder_1a3162979e4c679c7f5503cc4584949714) | Copies the current directory. |
| [`moveTo`](#class_folder_1a5002b388b7e503ba79a8623ca6c1cbbd) | Moves the current directory. |
| [`moveTo`](#class_folder_1a0ab690abfff790a2bd9fff3dd5976e82) | Moves the current directory. |
| [`moveTo`](#class_folder_1a3125db272185165a03b891efe5985a32) | Move the current directory. |

## Members

### `Folder` <a id="class_folder_1a8af69fd19ba86816c60b4c2291311eb1" class="anchor"></a>

```cpp
public Folder()
```

Creates an empty [Folder](#class_folder) object. Please note that any operation on this object will fail until a valid directory is assigned to it.

<hr />

### `Folder` <a id="class_folder_1aa2a4dc98e8c383c7b4fa503b45813fe3" class="anchor"></a>

```cpp
public Folder(const char * dirname)
```

Creates a directory with the specified name. If the directory already exists, it returns a [Folder](#class_folder) object representing the existing directory. Otherwise, it tries to create a new directory with the specified name. If it fails the `path` property of the [Folder](#class_folder) object will be null.

#### Parameters
* `const` char * dirname - The name of the directory.
<hr />

### `Folder` <a id="class_folder_1a6f445bfe0214a03ba00a1408e41726dd" class="anchor"></a>

```cpp
public Folder(String dirname)
```

Creates a directory with the specified name. If the directory already exists, it returns a [Folder](#class_folder) object representing the existing directory. Otherwise, it tries to create a new directory with the specified name. If it fails the `path` property of the [Folder](#class_folder) object will be empty.

#### Parameters
* `String` dirname - The name of the directory.
<hr />

### `createFile` <a id="class_folder_1a04eceb0406b02e2d8a628d3c359dba5d" class="anchor"></a>

```cpp
public UFile createFile(const char * fileName, FileMode fmode)
```

Creates a file inside the directory.

#### Parameters
* `const` char * fileName - The name of the file to create. 

#### Returns
A File object if successful, NULL if not.
<hr />

### `createFile` <a id="class_folder_1a44255e2c0c4ffa37d7637a601bc590f6" class="anchor"></a>

```cpp
public UFile createFile(String fileName, FileMode fmode)
```

Creates a file inside the directory.

#### Parameters
* `String` fileName - The name of the file to create. 

#### Returns
A File object if successful, NULL if not.
<hr />

### `remove` <a id="class_folder_1aca893daac6c6747895d50987cf9cf34c" class="anchor"></a>

```cpp
public bool remove()
```

Removes a directory.

#### Parameters
* `dirname` The name of the directory to remove. 

#### Returns
True if the directory was removed successfully, false otherwise.
<hr />

### `rename` <a id="class_folder_1adcbb7766d628810f716887d1e7e8d36f" class="anchor"></a>

```cpp
public bool rename(const char * newDirname)
```

Renames a directory.

#### Parameters
* `const` char * newDirname The new name of the directory. 

#### Returns
True if the directory was renamed successfully, false otherwise.
<hr />

### `rename` <a id="class_folder_1a14519c2a344ebfb8161c2bee2a2b5464" class="anchor"></a>

```cpp
public bool rename(String newDirname)
```

Renames a directory.

#### Parameters
* `String` newDirname The new name of the directory. 

#### Returns
True if the directory was renamed successfully, false otherwise.
<hr />

### `exists` <a id="class_folder_1aa548278d3ec09fd4abcaa827a79c40f4" class="anchor"></a>

```cpp
public bool exists()
```

Checks if the directory exists.

#### Returns
True if the directory exists, false otherwise.
<hr />

### `getPath` <a id="class_folder_1a0ef68289c526f8bf24020389c4e09e86" class="anchor"></a>

```cpp
public const char * getPath()
```

Returns the path of the file.

#### Returns
The path of the file as a const char *
<hr />

### `getPathAsString` <a id="class_folder_1ac816d0fe5674c4648e97423b6f9c51f8" class="anchor"></a>

```cpp
public String getPathAsString()
```

Returns the path of the file.

#### Returns
The path of the file as an Arduino String
<hr />

### `createSubfolder` <a id="class_folder_1a78f2f9b297f62b67c2e0656b15a95868" class="anchor"></a>

```cpp
public Folder createSubfolder(const char * subfolderName, bool overwrite)
```

Creates a subfolder in the directory.

#### Parameters
* `const` char * subfolderName - he name of the subfolder to create. 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
The created subfolder.
<hr />

### `createSubfolder` <a id="class_folder_1ab50743664becb7b2a1fb564b5513d69c" class="anchor"></a>

```cpp
public Folder createSubfolder(String subfolderName, bool overwrite)
```

Creates a subfolder in the directory.

#### Parameters
* `String` subfolderName - he name of the subfolder to create. 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
The created subfolder.
<hr />

### `getFiles` <a id="class_folder_1a2e7f604d19b8ad61524f86ade86ed4ad" class="anchor"></a>

```cpp
public std::vector< UFile > getFiles()
```

Returns File objects for all files in the current directory.

#### Returns
A std::vector of File objects representing the files in the directory.
<hr />

### `getFolders` <a id="class_folder_1a5554b8cc2fd1ca39dfccbd06bc635e10" class="anchor"></a>

```cpp
public std::vector< Folder > getFolders()
```

Returns [Folder](#class_folder) objects for all files in the current directory.

#### Returns
A std::vector of [Folder](#class_folder) objects representing the files in the directory.
<hr />

### `copyTo` <a id="class_folder_1aabf0818b7ee45b2d871e82e86edb4ebd" class="anchor"></a>

```cpp
public bool copyTo( Folder destination, bool overwrite)
```

Copies the current directory.

#### Parameters
* `[Folder](#class_folder)` destination - a [Folder](#class_folder) object representing the destination 

#### Returns
True upon success, false otherwise.
<hr />

### `copyTo` <a id="class_folder_1a058d193f53c559eefe343b30797500eb" class="anchor"></a>

```cpp
public bool copyTo(const char * destination, bool overwrite)
```

Copies the current directory.

#### Parameters
* `const` char * destination - the path of the destination location 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.
<hr />

### `copyTo` <a id="class_folder_1a3162979e4c679c7f5503cc4584949714" class="anchor"></a>

```cpp
public bool copyTo(String destination, bool overwrite)
```

Copies the current directory.

#### Parameters
* `String` destination - the path of the destination location 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.
<hr />

### `moveTo` <a id="class_folder_1a5002b388b7e503ba79a8623ca6c1cbbd" class="anchor"></a>

```cpp
public bool moveTo( Folder destination, bool overwrite)
```

Moves the current directory.

#### Parameters
* `[Folder](#class_folder)` destination - a [Folder](#class_folder) object representing the destination 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.
<hr />

### `moveTo` <a id="class_folder_1a0ab690abfff790a2bd9fff3dd5976e82" class="anchor"></a>

```cpp
public bool moveTo(const char * destination, bool overwrite)
```

Moves the current directory.

#### Parameters
* `const` char * destination - the path of the destination location 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.
<hr />

### `moveTo` <a id="class_folder_1a3125db272185165a03b891efe5985a32" class="anchor"></a>

```cpp
public bool moveTo(String destination, bool overwrite)
```

Move the current directory.

#### Parameters
* `String` destination - the path of the destination location 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.
<hr />

# class `InternalStorage` <a id="class_internal_storage" class="anchor"></a>

```cpp
class InternalStorage
  : public Arduino_UnifiedStorage
```

Represents internal storage using the Arduino Unified Storage library.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`InternalStorage`](#class_internal_storage_1ac45948ef554bc659efed81240140192e) | Constructs an [InternalStorage](#class_internal_storage) object with default settings. If no partitions are available, it restores the default partitioning scheme (See [restoreDefaultPartitions()](#class_internal_storage_1aa437dd0c91b3481f93fcd8239ed6dc82) for more info). If partitions are available, it sets the partition number, file system type, and partition name based on the last partition available. When using the default partitioning scheme the last partition would be the user partition. |
| [`InternalStorage`](#class_internal_storage_1ac13cad019a2ae66647d1c3604690eca7) | Constructs an [InternalStorage](#class_internal_storage) object with the specified partition, name, and file system. |
| [`begin`](#class_internal_storage_1a984731348dfbdade84e24250133a033e) | Initializes the internal storage. |
| [`begin`](#class_internal_storage_1a90cd409874d9c578ce3add4df88875e5) | Initializes the internal storage with the specified file system. |
| [`unmount`](#class_internal_storage_1a663446e2135a4e91d7fdb8ca638cc027) | Unmounts the internal storage. |
| [`getRootFolder`](#class_internal_storage_1a87142ddbdad62217e33851b32572082d) | Retrieves the root folder of the internal storage. |
| [`format`](#class_internal_storage_1a9ee819a55de5d411e6b10bdc9942c601) | Formats the internal storage with the selected file system. |
| [`getBlockDevice`](#class_internal_storage_1af347558e09045a5dd868f93b24286bab) | Retrieves the block device associated with the internal storage. |
| [`partition`](#class_internal_storage_1aa184679273e351e17a3a713d36aba6aa) | Partitions the internal storage according to the partitioning scheme given in the `partitions` parameter erasing the existing partitions  |
| [`partition`](#class_internal_storage_1a6e9670923ace01a0ffba456ae460b1bb) | Creates one partition spanning over the whole size of the internal storage drive erasing the existing partitions.  |
| [`restoreDefaultPartitions`](#class_internal_storage_1aa437dd0c91b3481f93fcd8239ed6dc82) | Restores the default partitioning scheme (1MB FAT32 for Certificates, 5MB FAT32 for OTA, 8MB user storage) to the internal storage drive erasing the existing partitions.  |
| [`readPartitions`](#class_internal_storage_1a044927dfb048440a9c73985af9c3cf80) | Reads the partitioning scheme from the MBR sector of the internal storage drive and returns a vector of structs of type [Partition](#struct_partition) that represents the partitioning scheme  |

## Members

### `InternalStorage` <a id="class_internal_storage_1ac45948ef554bc659efed81240140192e" class="anchor"></a>

```cpp
public InternalStorage()
```

Constructs an [InternalStorage](#class_internal_storage) object with default settings. If no partitions are available, it restores the default partitioning scheme (See [restoreDefaultPartitions()](#class_internal_storage_1aa437dd0c91b3481f93fcd8239ed6dc82) for more info). If partitions are available, it sets the partition number, file system type, and partition name based on the last partition available. When using the default partitioning scheme the last partition would be the user partition.
<hr />

### `InternalStorage` <a id="class_internal_storage_1ac13cad019a2ae66647d1c3604690eca7" class="anchor"></a>

```cpp
public InternalStorage(int partition, const char * name, FileSystems fs)
```

Constructs an [InternalStorage](#class_internal_storage) object with the specified partition, name, and file system.

#### Parameters
* `partition` The partition number. 

* `name` The name of the partition. 

* `fs` The desired file system (FS_FAT or FS_LITTLEFS).
<hr />

### `begin` <a id="class_internal_storage_1a984731348dfbdade84e24250133a033e" class="anchor"></a>

```cpp
public virtual bool begin()
```

Initializes the internal storage.

#### Returns
true if successful, false if failed.
<hr />

### `begin` <a id="class_internal_storage_1a90cd409874d9c578ce3add4df88875e5" class="anchor"></a>

```cpp
public virtual bool begin(FileSystems fs)
```

Initializes the internal storage with the specified file system.

#### Parameters
* `fs` The desired file system (FS_FAT or FS_LITTLEFS). 

#### Returns
true if successful, false if failed.
<hr />

### `unmount` <a id="class_internal_storage_1a663446e2135a4e91d7fdb8ca638cc027" class="anchor"></a>

```cpp
public virtual bool unmount()
```

Unmounts the internal storage.

#### Returns
true if successful, false if failed.
<hr />

### `getRootFolder` <a id="class_internal_storage_1a87142ddbdad62217e33851b32572082d" class="anchor"></a>

```cpp
public virtual Folder getRootFolder()
```

Retrieves the root folder of the internal storage.

#### Returns
The root folder as a [Folder](#class_folder) object.
<hr />

### `format` <a id="class_internal_storage_1a9ee819a55de5d411e6b10bdc9942c601" class="anchor"></a>

```cpp
public virtual bool format(FileSystems fs)
```

Formats the internal storage with the selected file system.

#### Returns
true if successful, false if failed.
<hr />

### `getBlockDevice` <a id="class_internal_storage_1af347558e09045a5dd868f93b24286bab" class="anchor"></a>

```cpp
public BlockDeviceType * getBlockDevice()
```

Retrieves the block device associated with the internal storage.

#### Returns
The block device as a BlockDevice object.
<hr />

### `partition` <a id="class_internal_storage_1aa184679273e351e17a3a713d36aba6aa" class="anchor"></a>

```cpp
public static bool partition(std::vector< Partition > partitions)
```

Partitions the internal storage according to the partitioning scheme given in the `partitions` parameter erasing the existing partitions 
#### Parameters
* `partitions` - vector of structs of type [Partition](#struct_partition) that represents the partitioning scheme 

#### Returns
true if successful, false if failed.
<hr />

### `partition` <a id="class_internal_storage_1a6e9670923ace01a0ffba456ae460b1bb" class="anchor"></a>

```cpp
public static bool partition()
```

Creates one partition spanning over the whole size of the internal storage drive erasing the existing partitions. 
#### Returns
true if successful, false if failed.
<hr />

### `restoreDefaultPartitions` <a id="class_internal_storage_1aa437dd0c91b3481f93fcd8239ed6dc82" class="anchor"></a>

```cpp
public static bool restoreDefaultPartitions()
```

Restores the default partitioning scheme (1MB FAT32 for Certificates, 5MB FAT32 for OTA, 8MB user storage) to the internal storage drive erasing the existing partitions. 
#### Returns
true if successful, false if failed.
<hr />

### `readPartitions` <a id="class_internal_storage_1a044927dfb048440a9c73985af9c3cf80" class="anchor"></a>

```cpp
public static std::vector< Partition > readPartitions()
```

Reads the partitioning scheme from the MBR sector of the internal storage drive and returns a vector of structs of type [Partition](#struct_partition) that represents the partitioning scheme 
#### Returns
vector of structs of type [Partition](#struct_partition)
<hr />

# class `Partitioning` <a id="class_partitioning" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`eraseMBRSector`](#class_partitioning_1a21c0af41e2f29f3290dee36eb0f0d0b7) | Erases the first block (4096 bytes) of the BlockDevice to delete any already existing MBR partition table  |
| [`partitionDrive`](#class_partitioning_1a450e1491d5d58d5d082dba6d45561b0f) | Partitions the BlockDevice according to the partitioning schemme given by the vector of [Partition](#struct_partition) structs  |
| [`readPartitions`](#class_partitioning_1a21af9f41711668d2f80fb0c74ce9168f) | Reads and unpacks the MBR partition information and returns a list of partitions it can find on the drive  |

## Members

### `eraseMBRSector` <a id="class_partitioning_1a21c0af41e2f29f3290dee36eb0f0d0b7" class="anchor"></a>

```cpp
public static bool eraseMBRSector(BlockDeviceType * blockDevice)
```

Erases the first block (4096 bytes) of the BlockDevice to delete any already existing MBR partition table 
#### Parameters
* `The` BlockDevice on which the MBR sector is situated. 

#### Returns
True upon success, False on failure
<hr />

### `partitionDrive` <a id="class_partitioning_1a450e1491d5d58d5d082dba6d45561b0f" class="anchor"></a>

```cpp
public static bool partitionDrive(BlockDeviceType * blockDevice, std::vector< Partition > partitions)
```

Partitions the BlockDevice according to the partitioning schemme given by the vector of [Partition](#struct_partition) structs 
#### Parameters
* `blockDevice` - the BlockDevice which we would like to partition. 

* `partitions` - a vector of [Partition](#struct_partition) structs that represents the partitioning scheme 

#### Returns
True upon success, False on failure
<hr />

### `readPartitions` <a id="class_partitioning_1a21af9f41711668d2f80fb0c74ce9168f" class="anchor"></a>

```cpp
public static std::vector< Partition > readPartitions(BlockDeviceType * blockDevice)
```

Reads and unpacks the MBR partition information and returns a list of partitions it can find on the drive 
#### Parameters
* `blockDevice` on which the MBR sector is situated. 

#### Returns
std::vector of [Partition](#struct_partition) containing size and filesystem information about each partition
<hr />

# class `SDStorage` <a id="class_s_d_storage" class="anchor"></a>

```cpp
class SDStorage
  : public Arduino_UnifiedStorage
```

Represents an SD card storage using the Arduino Unified Storage library.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`SDStorage`](#class_s_d_storage_1a992cb710f41462a7a35c6dfdc838f01f) | Default constructor for the [SDStorage](#class_s_d_storage) class. |
| [`begin`](#class_s_d_storage_1ab49c772b785b6c97940baca60ae386ec) | Initializes the SD card storage. |
| [`begin`](#class_s_d_storage_1a19520df98c5a52d403ac26a873f65860) | Initializes the SD card storage with the specified file system. |
| [`unmount`](#class_s_d_storage_1a6f4d671e685d660d0aff8648d8288b9c) | Unmounts the SD card storage. |
| [`getRootFolder`](#class_s_d_storage_1a2f7327c327985d88bd1305310ec0c5e8) | Retrieves the root folder of the SD card storage. |
| [`format`](#class_s_d_storage_1a93cac8330a5950138985e3712db1dc07) | Formats the SD card storage with the selected file system. |

## Members

### `SDStorage` <a id="class_s_d_storage_1a992cb710f41462a7a35c6dfdc838f01f" class="anchor"></a>

```cpp
public SDStorage()
```

Default constructor for the [SDStorage](#class_s_d_storage) class.
<hr />

### `begin` <a id="class_s_d_storage_1ab49c772b785b6c97940baca60ae386ec" class="anchor"></a>

```cpp
public virtual bool begin()
```

Initializes the SD card storage.

#### Returns
true if successful, false if failed.
<hr />

### `begin` <a id="class_s_d_storage_1a19520df98c5a52d403ac26a873f65860" class="anchor"></a>

```cpp
public virtual bool begin(FileSystems fs)
```

Initializes the SD card storage with the specified file system.

#### Parameters
* `fs` The desired file system (FS_FAT or FS_LITTLEFS). 

#### Returns
true if successful, false if failed.
<hr />

### `unmount` <a id="class_s_d_storage_1a6f4d671e685d660d0aff8648d8288b9c" class="anchor"></a>

```cpp
public virtual bool unmount()
```

Unmounts the SD card storage.

#### Returns
true if successful, false if failed.
<hr />

### `getRootFolder` <a id="class_s_d_storage_1a2f7327c327985d88bd1305310ec0c5e8" class="anchor"></a>

```cpp
public virtual Folder getRootFolder()
```

Retrieves the root folder of the SD card storage.

#### Returns
The root folder as a [Folder](#class_folder) object.
<hr />

### `format` <a id="class_s_d_storage_1a93cac8330a5950138985e3712db1dc07" class="anchor"></a>

```cpp
public virtual bool format(FileSystems fs)
```

Formats the SD card storage with the selected file system.

#### Returns
true if successful, false if failed.
<hr />

# class `UFile` <a id="class_u_file" class="anchor"></a>

Class representing a File

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`UFile`](#class_u_file_1a2a04504d0135d28465e0547bec062ebf) | Constructor. |
| [`UFile`](#class_u_file_1acdd969b1c2f115fc105f6d08bd67b121) | Constructor. |
| [`~UFile`](#class_u_file_1a4f74e28f98898e3603140b6409fa52ba) |  |
| [`changeMode`](#class_u_file_1a744ad88f2037e87e3f5375c7aec28f6d) | Closes the file, and opens it again with a new file mode. |
| [`open`](#class_u_file_1aa52ff2913386374e6e83ba35f595d213) | Opens a file with the specified mode. |
| [`open`](#class_u_file_1a0247abf7053b47463f73ca8cb1c7c23c) | Opens a file with the specified mode. |
| [`close`](#class_u_file_1ab5731b8e40a87a44a7322bf151597c55) | Closes the file and releases any allocated resources. |
| [`seek`](#class_u_file_1aa117a19e5efe6508e5e87ab65abbb560) | Seeks to a specific position in the file. |
| [`read`](#class_u_file_1a8192f041831d58ba8186798676c5ad3a) | Reads data from the file into a buffer. |
| [`readAsString`](#class_u_file_1ad70a29b0e436906bdaa7b99e3fc9e1b3) | Reads the contents of the file as an Arduino String. |
| [`write`](#class_u_file_1a16625e123db35bf19f9088828d9e1305) | Writes data to the file from a buffer. |
| [`write`](#class_u_file_1a68ee9ecdb0a6efd9816f3382de67905e) | Writes a string to the file. |
| [`remove`](#class_u_file_1a0e9efb7c54053b6f507f6caa704fc101) | Removes the file. |
| [`rename`](#class_u_file_1a0511c1a498bcbce549b49db9e188c2c0) | Renames the file. |
| [`rename`](#class_u_file_1a2122cd3e0e16481ecaff1af897790c03) | Renames the file. |
| [`exists`](#class_u_file_1a4963afa70289718a3bd1ca50b6adb420) | Checks if the file exists. |
| [`copyTo`](#class_u_file_1a6178616dea1a897b0e4033dfdc7bc41d) | Copies the file to the specified destination path. |
| [`copyTo`](#class_u_file_1a908edbee6d38619798d63f72f8f58dd1) | Copies the file to the specified destination path. |
| [`copyTo`](#class_u_file_1a9e06719446533b73505a6f6a66091fa7) | Copies the file to the specified destination path. |
| [`moveTo`](#class_u_file_1abadd4af5700d94b2c3d74dd4dce51bdc) | Moves the file to the specified destination path. |
| [`moveTo`](#class_u_file_1ae676e42f3e5ad423da3386985fc8261f) | Moves the file to the specified destination path. |
| [`moveTo`](#class_u_file_1a69f6a7cccce8cc40eb6698df15f38635) | Copies the file to the specified destination folder. |
| [`getParentFolder`](#class_u_file_1a087b79b6d62a3ed122d1f8b0f25b0d24) | Returns a reference to the parent folder of the current folder. |
| [`getPath`](#class_u_file_1a122edcf553a8929b703d70c6aa8a6e80) | Returns the path of the directory. |
| [`getPathAsString`](#class_u_file_1a5adef9f3d538f92e51e52c4b1f3ada76) | Returns the path of the directory. |
| [`available`](#class_u_file_1a82ad0fb6cffaf23aea794b508ec57bbb) | Returns the number of bytes available to read. |
| [`read`](#class_u_file_1a62b544ebe9c3b144268016e6427917b5) | Returns one byte from the file. |
| [`write`](#class_u_file_1a4db87498c1a4205145816c14df704de7) | Writes one byte to the file. |

## Members

### `UFile` <a id="class_u_file_1a2a04504d0135d28465e0547bec062ebf" class="anchor"></a>

```cpp
public UFile()
```

Constructor.

<hr />

### `UFile` <a id="class_u_file_1acdd969b1c2f115fc105f6d08bd67b121" class="anchor"></a>

```cpp
public UFile(const char * path)
```

Constructor.

#### Parameters
* `const` char * path - path of the file
<hr />

### `~UFile` <a id="class_u_file_1a4f74e28f98898e3603140b6409fa52ba" class="anchor"></a>

```cpp
public ~UFile()
```

<hr />

### `changeMode` <a id="class_u_file_1a744ad88f2037e87e3f5375c7aec28f6d" class="anchor"></a>

```cpp
public bool changeMode(FileMode mode)
```

Closes the file, and opens it again with a new file mode.

#### Parameters
* `mode` The file mode (READ, WRITE, or APPEND). 

#### Returns
True if operation was successful, false otherwise.
<hr />

### `open` <a id="class_u_file_1aa52ff2913386374e6e83ba35f595d213" class="anchor"></a>

```cpp
public bool open(const char * filename, FileMode mode)
```

Opens a file with the specified mode.

#### Parameters
* `const` char * filename - The name of the file to open. 

* `mode` The file mode (READ, WRITE, or APPEND). 

#### Returns
True if the file was opened successfully, false otherwise.
<hr />

### `open` <a id="class_u_file_1a0247abf7053b47463f73ca8cb1c7c23c" class="anchor"></a>

```cpp
public bool open(String filename, FileMode mode)
```

Opens a file with the specified mode.

#### Parameters
* `String` filename - The name of the file to open. 

* `mode` The file mode (READ, WRITE, or APPEND). 

#### Returns
True if the file was opened successfully, false otherwise.
<hr />

### `close` <a id="class_u_file_1ab5731b8e40a87a44a7322bf151597c55" class="anchor"></a>

```cpp
public void close()
```

Closes the file and releases any allocated resources.

<hr />

### `seek` <a id="class_u_file_1aa117a19e5efe6508e5e87ab65abbb560" class="anchor"></a>

```cpp
public bool seek(size_t offset)
```

Seeks to a specific position in the file.

#### Parameters
* `offset` The offset from the beginning of the file. 

#### Returns
True if the seek operation was successful, false otherwise.
<hr />

### `read` <a id="class_u_file_1a8192f041831d58ba8186798676c5ad3a" class="anchor"></a>

```cpp
public size_t read(uint8_t * buffer, size_t size)
```

Reads data from the file into a buffer.

#### Parameters
* `buffer` The buffer to read data into. 

* `size` The size of the buffer. 

#### Returns
The number of bytes read from the file.
<hr />

### `readAsString` <a id="class_u_file_1ad70a29b0e436906bdaa7b99e3fc9e1b3" class="anchor"></a>

```cpp
public String readAsString()
```

Reads the contents of the file as an Arduino String.

#### Returns
The file contents as a String.
<hr />

### `write` <a id="class_u_file_1a16625e123db35bf19f9088828d9e1305" class="anchor"></a>

```cpp
public size_t write(const uint8_t * buffer, size_t size)
```

Writes data to the file from a buffer.

#### Parameters
* `buffer` The buffer containing the data to write. 

* `size` The size of the data to write. 

#### Returns
The number of bytes written to the file.
<hr />

### `write` <a id="class_u_file_1a68ee9ecdb0a6efd9816f3382de67905e" class="anchor"></a>

```cpp
public size_t write(String)
```

Writes a string to the file.

#### Parameters
* `data` The string to write. 

#### Returns
The number of bytes written to the file.
<hr />

### `remove` <a id="class_u_file_1a0e9efb7c54053b6f507f6caa704fc101" class="anchor"></a>

```cpp
public bool remove()
```

Removes the file.

#### Returns
True if the file was removed successfully, false otherwise.
<hr />

### `rename` <a id="class_u_file_1a0511c1a498bcbce549b49db9e188c2c0" class="anchor"></a>

```cpp
public bool rename(const char * newFilename)
```

Renames the file.

#### Parameters
* `const` char * newFilename The new name of the file. 

#### Returns
True if the file was renamed successfully, false otherwise.
<hr />

### `rename` <a id="class_u_file_1a2122cd3e0e16481ecaff1af897790c03" class="anchor"></a>

```cpp
public bool rename(String newFilename)
```

Renames the file.

#### Parameters
* `String` newFilename The new name of the file. 

#### Returns
True if the file was renamed successfully, false otherwise.
<hr />

### `exists` <a id="class_u_file_1a4963afa70289718a3bd1ca50b6adb420" class="anchor"></a>

```cpp
public bool exists()
```

Checks if the file exists.

#### Returns
True if the file exists, false otherwise.
<hr />

### `copyTo` <a id="class_u_file_1a6178616dea1a897b0e4033dfdc7bc41d" class="anchor"></a>

```cpp
public bool copyTo(const char * destinationPath, bool overwrite)
```

Copies the file to the specified destination path.

#### Parameters
* `const` char * destinationPath - The destination path to copy the file to. 

#### Returns
True upon success, false otherwise.
<hr />

### `copyTo` <a id="class_u_file_1a908edbee6d38619798d63f72f8f58dd1" class="anchor"></a>

```cpp
public bool copyTo(String destinationPath, bool overwrite)
```

Copies the file to the specified destination path.

#### Parameters
* `String` destinationPath The destination path to copy the file to. 

#### Returns
True upon success, false otherwise.
<hr />

### `copyTo` <a id="class_u_file_1a9e06719446533b73505a6f6a66091fa7" class="anchor"></a>

```cpp
public bool copyTo( Folder destinationFolder, bool overwrite)
```

Copies the file to the specified destination path.

#### Parameters
* `[Folder](#class_folder)` destinationPath - The destination folder to copy the file to. 

#### Returns
True upon success, false otherwise.
<hr />

### `moveTo` <a id="class_u_file_1abadd4af5700d94b2c3d74dd4dce51bdc" class="anchor"></a>

```cpp
public bool moveTo(const char * destinationPath, bool overwrite)
```

Moves the file to the specified destination path.

#### Parameters
* `const` char * destinationPath The destination path to move the file to. 

#### Returns
True upon success, false otherwise.
<hr />

### `moveTo` <a id="class_u_file_1ae676e42f3e5ad423da3386985fc8261f" class="anchor"></a>

```cpp
public bool moveTo(String destinationPath, bool overwrite)
```

Moves the file to the specified destination path.

#### Parameters
* `String` destinationPath The destination path to move the file to. 

#### Returns
True upon success, false otherwise.
<hr />

### `moveTo` <a id="class_u_file_1a69f6a7cccce8cc40eb6698df15f38635" class="anchor"></a>

```cpp
public bool moveTo( Folder destinationFolder, bool overwrite)
```

Copies the file to the specified destination folder.

#### Parameters
* `[Folder](#class_folder)` destinationFolder The destination directory to move the file to. 

#### Returns
True upon success, false otherwise.
<hr />

### `getParentFolder` <a id="class_u_file_1a087b79b6d62a3ed122d1f8b0f25b0d24" class="anchor"></a>

```cpp
public Folder getParentFolder()
```

Returns a reference to the parent folder of the current folder.

#### Returns
A directory object representing the current folder.
<hr />

### `getPath` <a id="class_u_file_1a122edcf553a8929b703d70c6aa8a6e80" class="anchor"></a>

```cpp
public const char * getPath()
```

Returns the path of the directory.

#### Returns
The path of the file as a const char *
<hr />

### `getPathAsString` <a id="class_u_file_1a5adef9f3d538f92e51e52c4b1f3ada76" class="anchor"></a>

```cpp
public String getPathAsString()
```

Returns the path of the directory.

#### Returns
The path of the file as a String
<hr />

### `available` <a id="class_u_file_1a82ad0fb6cffaf23aea794b508ec57bbb" class="anchor"></a>

```cpp
public uint32_t available()
```

Returns the number of bytes available to read.

#### Returns
The number of bytes available to read as int
<hr />

### `read` <a id="class_u_file_1a62b544ebe9c3b144268016e6427917b5" class="anchor"></a>

```cpp
public int read()
```

Returns one byte from the file.

#### Returns
An int representing one byte from the file
<hr />

### `write` <a id="class_u_file_1a4db87498c1a4205145816c14df704de7" class="anchor"></a>

```cpp
public size_t write(uint8_t value)
```

Writes one byte to the file.

#### Parameters
* `a` uint8_t value representing the byte to write
<hr />

# class `USBStorage` <a id="class_u_s_b_storage" class="anchor"></a>

```cpp
class USBStorage
  : public Arduino_UnifiedStorage
```

[USBStorage](#class_u_s_b_storage) class provides an interface to access USB storage devices. It inherits from the [Arduino_UnifiedStorage](#class_arduino___unified_storage) class and implements its pure virtual functions.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`USBStorage`](#class_u_s_b_storage_1ad084f3bd2479b0a1daa88013f3cfe23a) | Default constructor for the [USBStorage](#class_u_s_b_storage) class. |
| [`begin`](#class_u_s_b_storage_1aabf0868054a1741ffe4018301d145cb1) | Initializes the USB storage. |
| [`begin`](#class_u_s_b_storage_1a9fac27a863b6d73bb78f956be4517f67) | Initializes the USB storage with the specified file system. |
| [`unmount`](#class_u_s_b_storage_1acb602dc07465880ebaec64dca1b36506) | Unmounts the USB storage. |
| [`getRootFolder`](#class_u_s_b_storage_1a1d39336ddd7ec401dc2ed99c3117af59) | Retrieves the root folder of the USB storage. |
| [`format`](#class_u_s_b_storage_1a8aec32e4e48d081183ad880a61836bc5) | Formats the USB storage with the selected file system. |
| [`isMounted`](#class_u_s_b_storage_1a2d3e3a732f2a43ab67e2fcd05e4ac058) | Checks if the USB storage is mounted. |
| [`onConnect`](#class_u_s_b_storage_1a1dfb2b9dde7fbdc26c0bf73be9babe25) | Sets the callback function to be called when a USB connection is established. |
| [`removeOnConnectCallback`](#class_u_s_b_storage_1afc58782a3f5207356d29392cb31730a0) | Removes the callback function that is executed when the USB storage device is connected. |
| [`onDisconnect`](#class_u_s_b_storage_1a10ac0c8965eee6041b384a4823bb9720) | Sets a callback function to be called when the USB storage device is disconnected. |
| [`removeOnDisconnectCallback`](#class_u_s_b_storage_1a2333fb1697b7ca72e5127cf60fc6680f) | Removes the callback function that is called when the USB storage device is disconnected. |

## Members

### `USBStorage` <a id="class_u_s_b_storage_1ad084f3bd2479b0a1daa88013f3cfe23a" class="anchor"></a>

```cpp
public USBStorage()
```

Default constructor for the [USBStorage](#class_u_s_b_storage) class.
<hr />

### `begin` <a id="class_u_s_b_storage_1aabf0868054a1741ffe4018301d145cb1" class="anchor"></a>

```cpp
public virtual bool begin()
```

Initializes the USB storage.

#### Returns
true if successful, false if failed.
<hr />

### `begin` <a id="class_u_s_b_storage_1a9fac27a863b6d73bb78f956be4517f67" class="anchor"></a>

```cpp
public virtual bool begin(FileSystems fs)
```

Initializes the USB storage with the specified file system.

#### Parameters
* `fs` The desired file system (FS_FAT or FS_LITTLEFS). 

#### Returns
true if successful, false if failed.
<hr />

### `unmount` <a id="class_u_s_b_storage_1acb602dc07465880ebaec64dca1b36506" class="anchor"></a>

```cpp
public virtual bool unmount()
```

Unmounts the USB storage.

#### Returns
true if successful, false if failed.
<hr />

### `getRootFolder` <a id="class_u_s_b_storage_1a1d39336ddd7ec401dc2ed99c3117af59" class="anchor"></a>

```cpp
public virtual Folder getRootFolder()
```

Retrieves the root folder of the USB storage.

#### Returns
The root folder as a [Folder](#class_folder) object.
<hr />

### `format` <a id="class_u_s_b_storage_1a8aec32e4e48d081183ad880a61836bc5" class="anchor"></a>

```cpp
public virtual bool format(FileSystems fs)
```

Formats the USB storage with the selected file system.

#### Returns
true if successful, false if failed.
<hr />

### `isMounted` <a id="class_u_s_b_storage_1a2d3e3a732f2a43ab67e2fcd05e4ac058" class="anchor"></a>

```cpp
public bool isMounted()
```

Checks if the USB storage is mounted.

#### Returns
true if mounted, false otherwise.
<hr />

### `onConnect` <a id="class_u_s_b_storage_1a1dfb2b9dde7fbdc26c0bf73be9babe25" class="anchor"></a>

```cpp
public void onConnect(void(*)() callbackFunction)
```

Sets the callback function to be called when a USB connection is established.

#### Parameters
* `callbackFunction` A pointer to the function to be called when a USB connection is established.
<hr />

### `removeOnConnectCallback` <a id="class_u_s_b_storage_1afc58782a3f5207356d29392cb31730a0" class="anchor"></a>

```cpp
public void removeOnConnectCallback()
```

Removes the callback function that is executed when the USB storage device is connected.

<hr />

### `onDisconnect` <a id="class_u_s_b_storage_1a10ac0c8965eee6041b384a4823bb9720" class="anchor"></a>

```cpp
public void onDisconnect(void(*)() callbackFunction)
```

Sets a callback function to be called when the USB storage device is disconnected.

#### Parameters
* `callbackFunction` A pointer to the function to be called when the USB storage device is disconnected.
<hr />

### `removeOnDisconnectCallback` <a id="class_u_s_b_storage_1a2333fb1697b7ca72e5127cf60fc6680f" class="anchor"></a>

```cpp
public void removeOnDisconnectCallback()
```

Removes the callback function that is called when the USB storage device is disconnected.

<hr />

# struct `Partition` <a id="struct_partition" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`size`](#struct_partition_1a718bdba639f222d90d23480b58caa1f9) |  |
| [`fileSystemType`](#struct_partition_1af5c05bc6faa14fb253c3a39e5e883529) |  |

## Members

### `size` <a id="struct_partition_1a718bdba639f222d90d23480b58caa1f9" class="anchor"></a>

```cpp
public int size
```

<hr />

### `fileSystemType` <a id="struct_partition_1af5c05bc6faa14fb253c3a39e5e883529" class="anchor"></a>

```cpp
public FileSystems fileSystemType
```

<hr />

