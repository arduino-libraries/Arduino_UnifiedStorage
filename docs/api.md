# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`Arduino_UnifiedStorage`](#class_arduino___unified_storage) | Abstract class representing the common features of the supported storage methods
`class ` [`Folder`](#class_folder) | Class representing a directory.
`class ` [`InternalStorage`](#class_internal_storage) | Represents internal storage using the Arduino Unified Storage library.
`class ` [`SDStorage`](#class_s_d_storage) | Represents an SD card storage using the Arduino Unified Storage library.
`class ` [`UFile`](#class_u_file) | Class representing a File
`class ` [`USBStorage`](#class_u_s_b_storage) | Represents a USB storage using the Arduino Unified Storage library.

# class `Arduino_UnifiedStorage` <a id="class_arduino___unified_storage" class="anchor"></a>

Abstract class representing the common features of the supported storage methods

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int ` [`begin`](#class_arduino___unified_storage_1a65139ad70db5bc94d9192a94614b6ddd)`()` | Initializes the storage.
`public int ` [`begin`](#class_arduino___unified_storage_1a8875999ef2fdb12a98db1f0fcd0afc28)`(FileSystems fs)` | Initializes the storage with the specified file system. 
`public int ` [`unmount`](#class_arduino___unified_storage_1ad6ec554809fdf4a168a38d50c6b0096c)`()` | Unmounts the storage. 
`public ` [`Folder`](#class_folder)` ` [`getRootFolder`](#class_arduino___unified_storage_1a7166075ba695d54bf74c6c71b8c4c1bf)`()` | Retrieves the root folder of the storage. 
`public int ` [`formatLittleFS`](#class_arduino___unified_storage_1ac24d1b858dd5323c9ec1a3838a119c97)`()` | Formats the storage with the FAT file system. 
`public int ` [`formatFAT`](#class_arduino___unified_storage_1a33683ec5084c1108dd735f71a20d27a0)`()` | Formats the storage with the FAT file system.

## Members

### `public int ` [`begin`](#class_arduino___unified_storage_1a65139ad70db5bc94d9192a94614b6ddd)`()` <a id="class_arduino___unified_storage_1a65139ad70db5bc94d9192a94614b6ddd" class="anchor"></a>

Initializes the storage.

#### Returns
1 if successful, 0 if failed.

### `public int ` [`begin`](#class_arduino___unified_storage_1a8875999ef2fdb12a98db1f0fcd0afc28)`(FileSystems fs)` <a id="class_arduino___unified_storage_1a8875999ef2fdb12a98db1f0fcd0afc28" class="anchor"></a>

Initializes the storage with the specified file system. 
#### Parameters
* `fs` The desired file system (FS_FAT or FS_LITTLEFS). 

#### Returns
1 if successful, 0 if failed.

### `public int ` [`unmount`](#class_arduino___unified_storage_1ad6ec554809fdf4a168a38d50c6b0096c)`()` <a id="class_arduino___unified_storage_1ad6ec554809fdf4a168a38d50c6b0096c" class="anchor"></a>

Unmounts the storage. 
#### Returns
1 if successful, 0 if failed.

### `public ` [`Folder`](#class_folder)` ` [`getRootFolder`](#class_arduino___unified_storage_1a7166075ba695d54bf74c6c71b8c4c1bf)`()` <a id="class_arduino___unified_storage_1a7166075ba695d54bf74c6c71b8c4c1bf" class="anchor"></a>

Retrieves the root folder of the storage. 
#### Returns
The root folder as a [Folder](#class_folder) object.

### `public int ` [`formatLittleFS`](#class_arduino___unified_storage_1ac24d1b858dd5323c9ec1a3838a119c97)`()` <a id="class_arduino___unified_storage_1ac24d1b858dd5323c9ec1a3838a119c97" class="anchor"></a>

Formats the storage with the FAT file system. 
#### Returns
1 if successful, 0 if failed.

### `public int ` [`formatFAT`](#class_arduino___unified_storage_1a33683ec5084c1108dd735f71a20d27a0)`()` <a id="class_arduino___unified_storage_1a33683ec5084c1108dd735f71a20d27a0" class="anchor"></a>

Formats the storage with the FAT file system.

#### Returns
1 if successful, 0 if failed.

# class `Folder` <a id="class_folder" class="anchor"></a>

Class representing a directory.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`Folder`](#class_folder_1a8af69fd19ba86816c60b4c2291311eb1)`()` | Blank Constructor.
`public  ` [`Folder`](#class_folder_1aa2a4dc98e8c383c7b4fa503b45813fe3)`(const char * dirname)` | Constructor.
`public  ` [`Folder`](#class_folder_1a6f445bfe0214a03ba00a1408e41726dd)`(String dirname)` | Constructor.
`public ` [`UFile`](#class_u_file)` ` [`createFile`](#class_folder_1a04eceb0406b02e2d8a628d3c359dba5d)`(const char * fileName, FileMode fmode)` | Creates a file inside the directory.
`public ` [`UFile`](#class_u_file)` ` [`createFile`](#class_folder_1a44255e2c0c4ffa37d7637a601bc590f6)`(String fileName, FileMode fmode)` | Creates a file inside the directory.
`public bool ` [`remove`](#class_folder_1aca893daac6c6747895d50987cf9cf34c)`()` | Removes a directory.
`public bool ` [`rename`](#class_folder_1adcbb7766d628810f716887d1e7e8d36f)`(const char * newDirname)` | Renames a directory.
`public bool ` [`rename`](#class_folder_1a14519c2a344ebfb8161c2bee2a2b5464)`(String newDirname)` | Renames a directory.
`public bool ` [`exists`](#class_folder_1aa548278d3ec09fd4abcaa827a79c40f4)`()` | Checks if the directory exists.
`public const char * ` [`getPath`](#class_folder_1a731e8d84685eca8e273affba152468a6)`()` | Returns the path of the file.
`public String ` [`getPathString`](#class_folder_1a30dd952da8ae977dca4e3dfde8fbd5be)`()` | Returns the path of the file.
`public ` [`Folder`](#class_folder)` ` [`createSubfolder`](#class_folder_1a78f2f9b297f62b67c2e0656b15a95868)`(const char * subfolderName, bool overwrite)` | Creates a subfolder in the directory.
`public ` [`Folder`](#class_folder)` ` [`createSubfolder`](#class_folder_1ab50743664becb7b2a1fb564b5513d69c)`(String subfolderName, bool overwrite)` | Creates a subfolder in the directory.
`public std::vector< ` [`UFile`](#class_u_file)` > ` [`getFiles`](#class_folder_1a3c2e01e19b48e3aa709cbdbb0acbdd78)`()` | Returns File objects for all files in the current directory.
`public std::vector< ` [`Folder`](#class_folder)` > ` [`getFolders`](#class_folder_1a69d3df42dacbd1d64d0f527e090f1fbb)`()` | Returns [Folder](#class_folder) objects for all files in the current directory.
`public bool ` [`copyTo`](#class_folder_1aabf0818b7ee45b2d871e82e86edb4ebd)`(` [`Folder`](#class_folder)` destination, bool overwrite)` | Copies the current directory.
`public bool ` [`copyTo`](#class_folder_1a058d193f53c559eefe343b30797500eb)`(const char * destination, bool overwrite)` | Copies the current directory.
`public bool ` [`copyTo`](#class_folder_1a3162979e4c679c7f5503cc4584949714)`(String destination, bool overwrite)` | Copies the current directory.
`public bool ` [`moveTo`](#class_folder_1a5002b388b7e503ba79a8623ca6c1cbbd)`(` [`Folder`](#class_folder)` destination, bool overwrite)` | Moves the current directory.
`public bool ` [`moveTo`](#class_folder_1a0ab690abfff790a2bd9fff3dd5976e82)`(const char * destination, bool overwrite)` | Moves the current directory.
`public bool ` [`moveTo`](#class_folder_1a3125db272185165a03b891efe5985a32)`(String destination, bool overwrite)` | Move the current directory.
`private std::string ` [`dirname`](#class_folder_1a9a8a698e1d21f5aa0e10dc139d6d7f32) | 
`private std::string ` [`path`](#class_folder_1adbf6c881f9e745d724fc37ad4cea153f) | 
`private DIR * ` [`dir`](#class_folder_1ada2c04b7bb18988637ef5d03af23c53a) | 

## Members

### `public  ` [`Folder`](#class_folder_1a8af69fd19ba86816c60b4c2291311eb1)`()` <a id="class_folder_1a8af69fd19ba86816c60b4c2291311eb1" class="anchor"></a>

Blank Constructor.

### `public  ` [`Folder`](#class_folder_1aa2a4dc98e8c383c7b4fa503b45813fe3)`(const char * dirname)` <a id="class_folder_1aa2a4dc98e8c383c7b4fa503b45813fe3" class="anchor"></a>

Constructor.

#### Parameters
* `const` char * dirname - The name of the directory.

### `public  ` [`Folder`](#class_folder_1a6f445bfe0214a03ba00a1408e41726dd)`(String dirname)` <a id="class_folder_1a6f445bfe0214a03ba00a1408e41726dd" class="anchor"></a>

Constructor.

#### Parameters
* `String` dirname - The name of the directory.

### `public ` [`UFile`](#class_u_file)` ` [`createFile`](#class_folder_1a04eceb0406b02e2d8a628d3c359dba5d)`(const char * fileName, FileMode fmode)` <a id="class_folder_1a04eceb0406b02e2d8a628d3c359dba5d" class="anchor"></a>

Creates a file inside the directory.

#### Parameters
* `const` char * fileName - The name of the file to create. 

#### Returns
A File object if successful, NULL if not.

### `public ` [`UFile`](#class_u_file)` ` [`createFile`](#class_folder_1a44255e2c0c4ffa37d7637a601bc590f6)`(String fileName, FileMode fmode)` <a id="class_folder_1a44255e2c0c4ffa37d7637a601bc590f6" class="anchor"></a>

Creates a file inside the directory.

#### Parameters
* `String` fileName - The name of the file to create. 

#### Returns
A File object if successful, NULL if not.

### `public bool ` [`remove`](#class_folder_1aca893daac6c6747895d50987cf9cf34c)`()` <a id="class_folder_1aca893daac6c6747895d50987cf9cf34c" class="anchor"></a>

Removes a directory.

#### Parameters
* `dirname` The name of the directory to remove. 

#### Returns
True if the directory was removed successfully, false otherwise.

### `public bool ` [`rename`](#class_folder_1adcbb7766d628810f716887d1e7e8d36f)`(const char * newDirname)` <a id="class_folder_1adcbb7766d628810f716887d1e7e8d36f" class="anchor"></a>

Renames a directory.

#### Parameters
* `const` char * newDirname The new name of the directory. 

#### Returns
True if the directory was renamed successfully, false otherwise.

### `public bool ` [`rename`](#class_folder_1a14519c2a344ebfb8161c2bee2a2b5464)`(String newDirname)` <a id="class_folder_1a14519c2a344ebfb8161c2bee2a2b5464" class="anchor"></a>

Renames a directory.

#### Parameters
* `String` newDirname The new name of the directory. 

#### Returns
True if the directory was renamed successfully, false otherwise.

### `public bool ` [`exists`](#class_folder_1aa548278d3ec09fd4abcaa827a79c40f4)`()` <a id="class_folder_1aa548278d3ec09fd4abcaa827a79c40f4" class="anchor"></a>

Checks if the directory exists.

#### Returns
True if the directory exists, false otherwise.

### `public const char * ` [`getPath`](#class_folder_1a731e8d84685eca8e273affba152468a6)`()` <a id="class_folder_1a731e8d84685eca8e273affba152468a6" class="anchor"></a>

Returns the path of the file.

#### Returns
The path of the file as a const char *

### `public String ` [`getPathString`](#class_folder_1a30dd952da8ae977dca4e3dfde8fbd5be)`()` <a id="class_folder_1a30dd952da8ae977dca4e3dfde8fbd5be" class="anchor"></a>

Returns the path of the file.

#### Returns
The path of the file as an Arduino String

### `public ` [`Folder`](#class_folder)` ` [`createSubfolder`](#class_folder_1a78f2f9b297f62b67c2e0656b15a95868)`(const char * subfolderName, bool overwrite)` <a id="class_folder_1a78f2f9b297f62b67c2e0656b15a95868" class="anchor"></a>

Creates a subfolder in the directory.

#### Parameters
* `const` char * subfolderName - he name of the subfolder to create. 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
The created subfolder.

### `public ` [`Folder`](#class_folder)` ` [`createSubfolder`](#class_folder_1ab50743664becb7b2a1fb564b5513d69c)`(String subfolderName, bool overwrite)` <a id="class_folder_1ab50743664becb7b2a1fb564b5513d69c" class="anchor"></a>

Creates a subfolder in the directory.

#### Parameters
* `String` subfolderName - he name of the subfolder to create. 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
The created subfolder.

### `public std::vector< ` [`UFile`](#class_u_file)` > ` [`getFiles`](#class_folder_1a3c2e01e19b48e3aa709cbdbb0acbdd78)`()` <a id="class_folder_1a3c2e01e19b48e3aa709cbdbb0acbdd78" class="anchor"></a>

Returns File objects for all files in the current directory.

#### Returns
A std::vector of File objects representing the files in the directory.

### `public std::vector< ` [`Folder`](#class_folder)` > ` [`getFolders`](#class_folder_1a69d3df42dacbd1d64d0f527e090f1fbb)`()` <a id="class_folder_1a69d3df42dacbd1d64d0f527e090f1fbb" class="anchor"></a>

Returns [Folder](#class_folder) objects for all files in the current directory.

#### Returns
A std::vector of [Folder](#class_folder) objects representing the files in the directory.

### `public bool ` [`copyTo`](#class_folder_1aabf0818b7ee45b2d871e82e86edb4ebd)`(` [`Folder`](#class_folder)` destination, bool overwrite)` <a id="class_folder_1aabf0818b7ee45b2d871e82e86edb4ebd" class="anchor"></a>

Copies the current directory.

#### Parameters
* `[Folder](#class_folder)` destination - a [Folder](#class_folder) object representing the destination 

#### Returns
True upon success, false otherwise.

### `public bool ` [`copyTo`](#class_folder_1a058d193f53c559eefe343b30797500eb)`(const char * destination, bool overwrite)` <a id="class_folder_1a058d193f53c559eefe343b30797500eb" class="anchor"></a>

Copies the current directory.

#### Parameters
* `const` char * destination - the path of the destination location 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.

### `public bool ` [`copyTo`](#class_folder_1a3162979e4c679c7f5503cc4584949714)`(String destination, bool overwrite)` <a id="class_folder_1a3162979e4c679c7f5503cc4584949714" class="anchor"></a>

Copies the current directory.

#### Parameters
* `String` destination - the path of the destination location 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.

### `public bool ` [`moveTo`](#class_folder_1a5002b388b7e503ba79a8623ca6c1cbbd)`(` [`Folder`](#class_folder)` destination, bool overwrite)` <a id="class_folder_1a5002b388b7e503ba79a8623ca6c1cbbd" class="anchor"></a>

Moves the current directory.

#### Parameters
* `[Folder](#class_folder)` destination - a [Folder](#class_folder) object representing the destination 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.

### `public bool ` [`moveTo`](#class_folder_1a0ab690abfff790a2bd9fff3dd5976e82)`(const char * destination, bool overwrite)` <a id="class_folder_1a0ab690abfff790a2bd9fff3dd5976e82" class="anchor"></a>

Moves the current directory.

#### Parameters
* `const` char * destination - the path of the destination location 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.

### `public bool ` [`moveTo`](#class_folder_1a3125db272185165a03b891efe5985a32)`(String destination, bool overwrite)` <a id="class_folder_1a3125db272185165a03b891efe5985a32" class="anchor"></a>

Move the current directory.

#### Parameters
* `String` destination - the path of the destination location 

* `overwrite` - behaviour in case the folder already exists, default is false 

#### Returns
True upon success, false otherwise.

### `private std::string ` [`dirname`](#class_folder_1a9a8a698e1d21f5aa0e10dc139d6d7f32) <a id="class_folder_1a9a8a698e1d21f5aa0e10dc139d6d7f32" class="anchor"></a>

### `private std::string ` [`path`](#class_folder_1adbf6c881f9e745d724fc37ad4cea153f) <a id="class_folder_1adbf6c881f9e745d724fc37ad4cea153f" class="anchor"></a>

### `private DIR * ` [`dir`](#class_folder_1ada2c04b7bb18988637ef5d03af23c53a) <a id="class_folder_1ada2c04b7bb18988637ef5d03af23c53a" class="anchor"></a>

# class `InternalStorage` <a id="class_internal_storage" class="anchor"></a>

```
class InternalStorage
  : public Arduino_UnifiedStorage
```

Represents internal storage using the Arduino Unified Storage library.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`InternalStorage`](#class_internal_storage_1ac45948ef554bc659efed81240140192e)`()` | Default constructor for the [InternalStorage](#class_internal_storage) class.
`public  ` [`InternalStorage`](#class_internal_storage_1ac13cad019a2ae66647d1c3604690eca7)`(int partition, const char * name, FileSystems fs)` | Constructs an [InternalStorage](#class_internal_storage) object with the specified partition, name, and file system.
`public virtual int ` [`begin`](#class_internal_storage_1a520a40d49b3be7cc4b4ade86a9a8845b)`()` | Initializes the internal storage.
`public virtual int ` [`begin`](#class_internal_storage_1ace5153b8fbef34b9d0d6c8e3cf87007e)`(FileSystems fs)` | Initializes the internal storage with the specified file system.
`public virtual int ` [`unmount`](#class_internal_storage_1a3d139260d59add4222516aaf577a9399)`()` | Unmounts the internal storage.
`public virtual ` [`Folder`](#class_folder)` ` [`getRootFolder`](#class_internal_storage_1a87142ddbdad62217e33851b32572082d)`()` | Retrieves the root folder of the internal storage.
`public void ` [`setQSPIPartition`](#class_internal_storage_1a2ca8680537077ca3e189be2ca6dcc634)`(int partition)` | Sets the QSPI partition number.
`public void ` [`setQSPIPartitionName`](#class_internal_storage_1ae0fbe264a758a4026548df66ec05f8c8)`(const char * name)` | Sets the QSPI partition name.
`public virtual int ` [`formatFAT`](#class_internal_storage_1a8a1bea9b07a7a507e4d4ac6aafb75e12)`()` | Formats the internal storage with the FAT file system.
`public virtual int ` [`formatLittleFS`](#class_internal_storage_1a9e86d2bbc4cbafbaee58a4b2913e0830)`()` | Formats the internal storage with the LittleFS file system.
`private char * ` [`partitionName`](#class_internal_storage_1a831d504f992d398801924538b677b85c) | Retrieves the block device associated with the internal storage.
`private FileSystems ` [`fs`](#class_internal_storage_1a7bec9fbc7008259985da0460c501bca8) | 

## Members

### `public  ` [`InternalStorage`](#class_internal_storage_1ac45948ef554bc659efed81240140192e)`()` <a id="class_internal_storage_1ac45948ef554bc659efed81240140192e" class="anchor"></a>

Default constructor for the [InternalStorage](#class_internal_storage) class.

### `public  ` [`InternalStorage`](#class_internal_storage_1ac13cad019a2ae66647d1c3604690eca7)`(int partition, const char * name, FileSystems fs)` <a id="class_internal_storage_1ac13cad019a2ae66647d1c3604690eca7" class="anchor"></a>

Constructs an [InternalStorage](#class_internal_storage) object with the specified partition, name, and file system.

#### Parameters
* `partition` The partition number. 

* `name` The name of the partition. 

* `fs` The desired file system (FS_FAT or FS_LITTLEFS).

### `public virtual int ` [`begin`](#class_internal_storage_1a520a40d49b3be7cc4b4ade86a9a8845b)`()` <a id="class_internal_storage_1a520a40d49b3be7cc4b4ade86a9a8845b" class="anchor"></a>

Initializes the internal storage.

#### Returns
1 if successful, 0 if failed.

### `public virtual int ` [`begin`](#class_internal_storage_1ace5153b8fbef34b9d0d6c8e3cf87007e)`(FileSystems fs)` <a id="class_internal_storage_1ace5153b8fbef34b9d0d6c8e3cf87007e" class="anchor"></a>

Initializes the internal storage with the specified file system.

#### Parameters
* `fs` The desired file system (FS_FAT or FS_LITTLEFS). 

#### Returns
1 if successful, 0 if failed.

### `public virtual int ` [`unmount`](#class_internal_storage_1a3d139260d59add4222516aaf577a9399)`()` <a id="class_internal_storage_1a3d139260d59add4222516aaf577a9399" class="anchor"></a>

Unmounts the internal storage.

#### Returns
1 if successful, 0 if failed.

### `public virtual ` [`Folder`](#class_folder)` ` [`getRootFolder`](#class_internal_storage_1a87142ddbdad62217e33851b32572082d)`()` <a id="class_internal_storage_1a87142ddbdad62217e33851b32572082d" class="anchor"></a>

Retrieves the root folder of the internal storage.

#### Returns
The root folder as a [Folder](#class_folder) object.

### `public void ` [`setQSPIPartition`](#class_internal_storage_1a2ca8680537077ca3e189be2ca6dcc634)`(int partition)` <a id="class_internal_storage_1a2ca8680537077ca3e189be2ca6dcc634" class="anchor"></a>

Sets the QSPI partition number.

#### Parameters
* `partition` The partition number.

### `public void ` [`setQSPIPartitionName`](#class_internal_storage_1ae0fbe264a758a4026548df66ec05f8c8)`(const char * name)` <a id="class_internal_storage_1ae0fbe264a758a4026548df66ec05f8c8" class="anchor"></a>

Sets the QSPI partition name.

#### Parameters
* `name` The name of the partition.

### `public virtual int ` [`formatFAT`](#class_internal_storage_1a8a1bea9b07a7a507e4d4ac6aafb75e12)`()` <a id="class_internal_storage_1a8a1bea9b07a7a507e4d4ac6aafb75e12" class="anchor"></a>

Formats the internal storage with the FAT file system.

#### Returns
1 if successful, 0 if failed.

### `public virtual int ` [`formatLittleFS`](#class_internal_storage_1a9e86d2bbc4cbafbaee58a4b2913e0830)`()` <a id="class_internal_storage_1a9e86d2bbc4cbafbaee58a4b2913e0830" class="anchor"></a>

Formats the internal storage with the LittleFS file system.

#### Returns
1 if successful, 0 if failed.

### `private char * ` [`partitionName`](#class_internal_storage_1a831d504f992d398801924538b677b85c) <a id="class_internal_storage_1a831d504f992d398801924538b677b85c" class="anchor"></a>

Retrieves the block device associated with the internal storage.

#### Returns
The block device as a BlockDevice object.

### `private FileSystems ` [`fs`](#class_internal_storage_1a7bec9fbc7008259985da0460c501bca8) <a id="class_internal_storage_1a7bec9fbc7008259985da0460c501bca8" class="anchor"></a>

# class `SDStorage` <a id="class_s_d_storage" class="anchor"></a>

```
class SDStorage
  : public Arduino_UnifiedStorage
```

Represents an SD card storage using the Arduino Unified Storage library.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`SDStorage`](#class_s_d_storage_1a992cb710f41462a7a35c6dfdc838f01f)`()` | Default constructor for the [SDStorage](#class_s_d_storage) class.
`public virtual int ` [`begin`](#class_s_d_storage_1a2e46cdebf6b253b7a5d3efa41c019b84)`()` | Initializes the SD card storage.
`public virtual int ` [`begin`](#class_s_d_storage_1ab78cac5ad77a9b61cd586485755a6f8a)`(FileSystems fs)` | Initializes the SD card storage with the specified file system.
`public virtual int ` [`unmount`](#class_s_d_storage_1a29ed4a057be24972953d9bb52b7bd593)`()` | Unmounts the SD card storage.
`public virtual ` [`Folder`](#class_folder)` ` [`getRootFolder`](#class_s_d_storage_1a2f7327c327985d88bd1305310ec0c5e8)`()` | Retrieves the root folder of the SD card storage.
`public virtual int ` [`formatFAT`](#class_s_d_storage_1ab06c05a87f5e34036c2d69d187ea3775)`()` | Formats the SD card storage with the FAT file system.
`public virtual int ` [`formatLittleFS`](#class_s_d_storage_1a797b3226c20794fa140cea95e13d5cee)`()` | Formats the SD card storage with the LittleFS file system.
`private FileSystems ` [`fs`](#class_s_d_storage_1a711f6f2e8af27534e9cc4cb83146049b) | 

## Members

### `public  ` [`SDStorage`](#class_s_d_storage_1a992cb710f41462a7a35c6dfdc838f01f)`()` <a id="class_s_d_storage_1a992cb710f41462a7a35c6dfdc838f01f" class="anchor"></a>

Default constructor for the [SDStorage](#class_s_d_storage) class.

### `public virtual int ` [`begin`](#class_s_d_storage_1a2e46cdebf6b253b7a5d3efa41c019b84)`()` <a id="class_s_d_storage_1a2e46cdebf6b253b7a5d3efa41c019b84" class="anchor"></a>

Initializes the SD card storage.

#### Returns
1 if successful, 0 if failed.

### `public virtual int ` [`begin`](#class_s_d_storage_1ab78cac5ad77a9b61cd586485755a6f8a)`(FileSystems fs)` <a id="class_s_d_storage_1ab78cac5ad77a9b61cd586485755a6f8a" class="anchor"></a>

Initializes the SD card storage with the specified file system.

#### Parameters
* `fs` The desired file system (FS_FAT or FS_LITTLEFS). 

#### Returns
1 if successful, 0 if failed.

### `public virtual int ` [`unmount`](#class_s_d_storage_1a29ed4a057be24972953d9bb52b7bd593)`()` <a id="class_s_d_storage_1a29ed4a057be24972953d9bb52b7bd593" class="anchor"></a>

Unmounts the SD card storage.

#### Returns
1 if successful, 0 if failed.

### `public virtual ` [`Folder`](#class_folder)` ` [`getRootFolder`](#class_s_d_storage_1a2f7327c327985d88bd1305310ec0c5e8)`()` <a id="class_s_d_storage_1a2f7327c327985d88bd1305310ec0c5e8" class="anchor"></a>

Retrieves the root folder of the SD card storage.

#### Returns
The root folder as a [Folder](#class_folder) object.

### `public virtual int ` [`formatFAT`](#class_s_d_storage_1ab06c05a87f5e34036c2d69d187ea3775)`()` <a id="class_s_d_storage_1ab06c05a87f5e34036c2d69d187ea3775" class="anchor"></a>

Formats the SD card storage with the FAT file system.

#### Returns
1 if successful, 0 if failed.

### `public virtual int ` [`formatLittleFS`](#class_s_d_storage_1a797b3226c20794fa140cea95e13d5cee)`()` <a id="class_s_d_storage_1a797b3226c20794fa140cea95e13d5cee" class="anchor"></a>

Formats the SD card storage with the LittleFS file system.

#### Returns
1 if successful, 0 if failed.

### `private FileSystems ` [`fs`](#class_s_d_storage_1a711f6f2e8af27534e9cc4cb83146049b) <a id="class_s_d_storage_1a711f6f2e8af27534e9cc4cb83146049b" class="anchor"></a>

# class `UFile` <a id="class_u_file" class="anchor"></a>

Class representing a File

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`UFile`](#class_u_file_1a2a04504d0135d28465e0547bec062ebf)`()` | Constructor.
`public  ` [`UFile`](#class_u_file_1acdd969b1c2f115fc105f6d08bd67b121)`(const char * path)` | Constructor.
`public  ` [`~UFile`](#class_u_file_1a4f74e28f98898e3603140b6409fa52ba)`()` | 
`public bool ` [`changeMode`](#class_u_file_1a744ad88f2037e87e3f5375c7aec28f6d)`(FileMode mode)` | Closes the file, and opens it again with a new file mode.
`public bool ` [`open`](#class_u_file_1aa52ff2913386374e6e83ba35f595d213)`(const char * filename, FileMode mode)` | Opens a file with the specified mode.
`public bool ` [`open`](#class_u_file_1a0247abf7053b47463f73ca8cb1c7c23c)`(String filename, FileMode mode)` | Opens a file with the specified mode.
`public void ` [`close`](#class_u_file_1ab5731b8e40a87a44a7322bf151597c55)`()` | Closes the file and releases any allocated resources.
`public bool ` [`seek`](#class_u_file_1aa117a19e5efe6508e5e87ab65abbb560)`(size_t offset)` | Seeks to a specific position in the file.
`public size_t ` [`read`](#class_u_file_1a8192f041831d58ba8186798676c5ad3a)`(uint8_t * buffer, size_t size)` | Reads data from the file into a buffer.
`public String ` [`readAsString`](#class_u_file_1ad70a29b0e436906bdaa7b99e3fc9e1b3)`()` | Reads the contents of the file as an Arduino String.
`public size_t ` [`write`](#class_u_file_1a16625e123db35bf19f9088828d9e1305)`(const uint8_t * buffer, size_t size)` | Writes data to the file from a buffer.
`public size_t ` [`write`](#class_u_file_1a68ee9ecdb0a6efd9816f3382de67905e)`(String)` | Writes a string to the file.
`public bool ` [`remove`](#class_u_file_1a0e9efb7c54053b6f507f6caa704fc101)`()` | Removes the file.
`public bool ` [`rename`](#class_u_file_1a0511c1a498bcbce549b49db9e188c2c0)`(const char * newFilename)` | Renames the file.
`public bool ` [`rename`](#class_u_file_1a2122cd3e0e16481ecaff1af897790c03)`(String newFilename)` | Renames the file.
`public bool ` [`exists`](#class_u_file_1a4963afa70289718a3bd1ca50b6adb420)`()` | Checks if the file exists.
`public bool ` [`copyTo`](#class_u_file_1a6178616dea1a897b0e4033dfdc7bc41d)`(const char * destinationPath, bool overwrite)` | Copies the file to the specified destination path.
`public bool ` [`copyTo`](#class_u_file_1a908edbee6d38619798d63f72f8f58dd1)`(String destinationPath, bool overwrite)` | Copies the file to the specified destination path.
`public bool ` [`copyTo`](#class_u_file_1a9e06719446533b73505a6f6a66091fa7)`(` [`Folder`](#class_folder)` destinationFolder, bool overwrite)` | Copies the file to the specified destination path.
`public bool ` [`moveTo`](#class_u_file_1abadd4af5700d94b2c3d74dd4dce51bdc)`(const char * destinationPath, bool overwrite)` | Moves the file to the specified destination path.
`public bool ` [`moveTo`](#class_u_file_1ae676e42f3e5ad423da3386985fc8261f)`(String destinationPath, bool overwrite)` | Moves the file to the specified destination path.
`public bool ` [`moveTo`](#class_u_file_1a69f6a7cccce8cc40eb6698df15f38635)`(` [`Folder`](#class_folder)` destinationFolder, bool overwrite)` | Copies the file to the specified destination folder.
`public ` [`Folder`](#class_folder)` ` [`getParentFolder`](#class_u_file_1a087b79b6d62a3ed122d1f8b0f25b0d24)`()` | Returns a reference to the parent folder of the current folder.
`public const char * ` [`getPath`](#class_u_file_1a41592023ea53cd1b46f383097a3db1f8)`()` | Returns the path of the directory.
`public String ` [`getPathString`](#class_u_file_1a379d1f0076b414408bac26f317ffc204)`()` | Returns the path of the directory.
`public int ` [`available`](#class_u_file_1a37fbfdc0ad16ee06d4a66848b40912cd)`()` | Returns the number of bytes available to read.
`public int ` [`read`](#class_u_file_1a62b544ebe9c3b144268016e6427917b5)`()` | Returns one byte from the file.
`public size_t ` [`write`](#class_u_file_1a4db87498c1a4205145816c14df704de7)`(uint8_t value)` | Writes one byte to the file.
`private FILE * ` [`fp`](#class_u_file_1aeb2eaaab578ba6e4d25cd347ec8b8ba2) | 
`private uint8_t * ` [`readBuffer`](#class_u_file_1abcfa16a7593cd3c993cd3ac944c60ddb) | 
`private std::string ` [`path`](#class_u_file_1a19c3bc34bb3756ee19145ab259520d1a) | 
`private FileMode ` [`fm`](#class_u_file_1a2cfecc27dc709b4dafc9b97245348f90) | 

## Members

### `public  ` [`UFile`](#class_u_file_1a2a04504d0135d28465e0547bec062ebf)`()` <a id="class_u_file_1a2a04504d0135d28465e0547bec062ebf" class="anchor"></a>

Constructor.

### `public  ` [`UFile`](#class_u_file_1acdd969b1c2f115fc105f6d08bd67b121)`(const char * path)` <a id="class_u_file_1acdd969b1c2f115fc105f6d08bd67b121" class="anchor"></a>

Constructor.

#### Parameters
* `const` char * path - path of the file

### `public  ` [`~UFile`](#class_u_file_1a4f74e28f98898e3603140b6409fa52ba)`()` <a id="class_u_file_1a4f74e28f98898e3603140b6409fa52ba" class="anchor"></a>

### `public bool ` [`changeMode`](#class_u_file_1a744ad88f2037e87e3f5375c7aec28f6d)`(FileMode mode)` <a id="class_u_file_1a744ad88f2037e87e3f5375c7aec28f6d" class="anchor"></a>

Closes the file, and opens it again with a new file mode.

#### Parameters
* `mode` The file mode (READ, WRITE, or APPEND). 

#### Returns
True if operation was successful, false otherwise.

### `public bool ` [`open`](#class_u_file_1aa52ff2913386374e6e83ba35f595d213)`(const char * filename, FileMode mode)` <a id="class_u_file_1aa52ff2913386374e6e83ba35f595d213" class="anchor"></a>

Opens a file with the specified mode.

#### Parameters
* `const` char * filename - The name of the file to open. 

* `mode` The file mode (READ, WRITE, or APPEND). 

#### Returns
True if the file was opened successfully, false otherwise.

### `public bool ` [`open`](#class_u_file_1a0247abf7053b47463f73ca8cb1c7c23c)`(String filename, FileMode mode)` <a id="class_u_file_1a0247abf7053b47463f73ca8cb1c7c23c" class="anchor"></a>

Opens a file with the specified mode.

#### Parameters
* `String` filename - The name of the file to open. 

* `mode` The file mode (READ, WRITE, or APPEND). 

#### Returns
True if the file was opened successfully, false otherwise.

### `public void ` [`close`](#class_u_file_1ab5731b8e40a87a44a7322bf151597c55)`()` <a id="class_u_file_1ab5731b8e40a87a44a7322bf151597c55" class="anchor"></a>

Closes the file and releases any allocated resources.

### `public bool ` [`seek`](#class_u_file_1aa117a19e5efe6508e5e87ab65abbb560)`(size_t offset)` <a id="class_u_file_1aa117a19e5efe6508e5e87ab65abbb560" class="anchor"></a>

Seeks to a specific position in the file.

#### Parameters
* `offset` The offset from the beginning of the file. 

#### Returns
True if the seek operation was successful, false otherwise.

### `public size_t ` [`read`](#class_u_file_1a8192f041831d58ba8186798676c5ad3a)`(uint8_t * buffer, size_t size)` <a id="class_u_file_1a8192f041831d58ba8186798676c5ad3a" class="anchor"></a>

Reads data from the file into a buffer.

#### Parameters
* `buffer` The buffer to read data into. 

* `size` The size of the buffer. 

#### Returns
The number of bytes read from the file.

### `public String ` [`readAsString`](#class_u_file_1ad70a29b0e436906bdaa7b99e3fc9e1b3)`()` <a id="class_u_file_1ad70a29b0e436906bdaa7b99e3fc9e1b3" class="anchor"></a>

Reads the contents of the file as an Arduino String.

#### Returns
The file contents as a String.

### `public size_t ` [`write`](#class_u_file_1a16625e123db35bf19f9088828d9e1305)`(const uint8_t * buffer, size_t size)` <a id="class_u_file_1a16625e123db35bf19f9088828d9e1305" class="anchor"></a>

Writes data to the file from a buffer.

#### Parameters
* `buffer` The buffer containing the data to write. 

* `size` The size of the data to write. 

#### Returns
The number of bytes written to the file.

### `public size_t ` [`write`](#class_u_file_1a68ee9ecdb0a6efd9816f3382de67905e)`(String)` <a id="class_u_file_1a68ee9ecdb0a6efd9816f3382de67905e" class="anchor"></a>

Writes a string to the file.

#### Parameters
* `data` The string to write. 

#### Returns
The number of bytes written to the file.

### `public bool ` [`remove`](#class_u_file_1a0e9efb7c54053b6f507f6caa704fc101)`()` <a id="class_u_file_1a0e9efb7c54053b6f507f6caa704fc101" class="anchor"></a>

Removes the file.

#### Returns
True if the file was removed successfully, false otherwise.

### `public bool ` [`rename`](#class_u_file_1a0511c1a498bcbce549b49db9e188c2c0)`(const char * newFilename)` <a id="class_u_file_1a0511c1a498bcbce549b49db9e188c2c0" class="anchor"></a>

Renames the file.

#### Parameters
* `const` char * newFilename The new name of the file. 

#### Returns
True if the file was renamed successfully, false otherwise.

### `public bool ` [`rename`](#class_u_file_1a2122cd3e0e16481ecaff1af897790c03)`(String newFilename)` <a id="class_u_file_1a2122cd3e0e16481ecaff1af897790c03" class="anchor"></a>

Renames the file.

#### Parameters
* `String` newFilename The new name of the file. 

#### Returns
True if the file was renamed successfully, false otherwise.

### `public bool ` [`exists`](#class_u_file_1a4963afa70289718a3bd1ca50b6adb420)`()` <a id="class_u_file_1a4963afa70289718a3bd1ca50b6adb420" class="anchor"></a>

Checks if the file exists.

#### Returns
True if the file exists, false otherwise.

### `public bool ` [`copyTo`](#class_u_file_1a6178616dea1a897b0e4033dfdc7bc41d)`(const char * destinationPath, bool overwrite)` <a id="class_u_file_1a6178616dea1a897b0e4033dfdc7bc41d" class="anchor"></a>

Copies the file to the specified destination path.

#### Parameters
* `const` char * destinationPath - The destination path to copy the file to. 

#### Returns
True upon success, false otherwise.

### `public bool ` [`copyTo`](#class_u_file_1a908edbee6d38619798d63f72f8f58dd1)`(String destinationPath, bool overwrite)` <a id="class_u_file_1a908edbee6d38619798d63f72f8f58dd1" class="anchor"></a>

Copies the file to the specified destination path.

#### Parameters
* `String` destinationPath The destination path to copy the file to. 

#### Returns
True upon success, false otherwise.

### `public bool ` [`copyTo`](#class_u_file_1a9e06719446533b73505a6f6a66091fa7)`(` [`Folder`](#class_folder)` destinationFolder, bool overwrite)` <a id="class_u_file_1a9e06719446533b73505a6f6a66091fa7" class="anchor"></a>

Copies the file to the specified destination path.

#### Parameters
* `[Folder](#class_folder)` destinationPath - The destination folder to copy the file to. 

#### Returns
True upon success, false otherwise.

### `public bool ` [`moveTo`](#class_u_file_1abadd4af5700d94b2c3d74dd4dce51bdc)`(const char * destinationPath, bool overwrite)` <a id="class_u_file_1abadd4af5700d94b2c3d74dd4dce51bdc" class="anchor"></a>

Moves the file to the specified destination path.

#### Parameters
* `const` char * destinationPath The destination path to move the file to. 

#### Returns
True upon success, false otherwise.

### `public bool ` [`moveTo`](#class_u_file_1ae676e42f3e5ad423da3386985fc8261f)`(String destinationPath, bool overwrite)` <a id="class_u_file_1ae676e42f3e5ad423da3386985fc8261f" class="anchor"></a>

Moves the file to the specified destination path.

#### Parameters
* `String` destinationPath The destination path to move the file to. 

#### Returns
True upon success, false otherwise.

### `public bool ` [`moveTo`](#class_u_file_1a69f6a7cccce8cc40eb6698df15f38635)`(` [`Folder`](#class_folder)` destinationFolder, bool overwrite)` <a id="class_u_file_1a69f6a7cccce8cc40eb6698df15f38635" class="anchor"></a>

Copies the file to the specified destination folder.

#### Parameters
* `[Folder](#class_folder)` destinationFolder The destination directory to move the file to. 

#### Returns
True upon success, false otherwise.

### `public ` [`Folder`](#class_folder)` ` [`getParentFolder`](#class_u_file_1a087b79b6d62a3ed122d1f8b0f25b0d24)`()` <a id="class_u_file_1a087b79b6d62a3ed122d1f8b0f25b0d24" class="anchor"></a>

Returns a reference to the parent folder of the current folder.

#### Returns
A directory object representing the current folder.

### `public const char * ` [`getPath`](#class_u_file_1a41592023ea53cd1b46f383097a3db1f8)`()` <a id="class_u_file_1a41592023ea53cd1b46f383097a3db1f8" class="anchor"></a>

Returns the path of the directory.

#### Returns
The path of the file as a const char *

### `public String ` [`getPathString`](#class_u_file_1a379d1f0076b414408bac26f317ffc204)`()` <a id="class_u_file_1a379d1f0076b414408bac26f317ffc204" class="anchor"></a>

Returns the path of the directory.

#### Returns
The path of the file as a String

### `public int ` [`available`](#class_u_file_1a37fbfdc0ad16ee06d4a66848b40912cd)`()` <a id="class_u_file_1a37fbfdc0ad16ee06d4a66848b40912cd" class="anchor"></a>

Returns the number of bytes available to read.

#### Returns
The number of bytes available to read as int

### `public int ` [`read`](#class_u_file_1a62b544ebe9c3b144268016e6427917b5)`()` <a id="class_u_file_1a62b544ebe9c3b144268016e6427917b5" class="anchor"></a>

Returns one byte from the file.

#### Returns
An int representing one byte from the file

### `public size_t ` [`write`](#class_u_file_1a4db87498c1a4205145816c14df704de7)`(uint8_t value)` <a id="class_u_file_1a4db87498c1a4205145816c14df704de7" class="anchor"></a>

Writes one byte to the file.

#### Parameters
* `a` uint8_t value representing the byte to write

### `private FILE * ` [`fp`](#class_u_file_1aeb2eaaab578ba6e4d25cd347ec8b8ba2) <a id="class_u_file_1aeb2eaaab578ba6e4d25cd347ec8b8ba2" class="anchor"></a>

### `private uint8_t * ` [`readBuffer`](#class_u_file_1abcfa16a7593cd3c993cd3ac944c60ddb) <a id="class_u_file_1abcfa16a7593cd3c993cd3ac944c60ddb" class="anchor"></a>

### `private std::string ` [`path`](#class_u_file_1a19c3bc34bb3756ee19145ab259520d1a) <a id="class_u_file_1a19c3bc34bb3756ee19145ab259520d1a" class="anchor"></a>

### `private FileMode ` [`fm`](#class_u_file_1a2cfecc27dc709b4dafc9b97245348f90) <a id="class_u_file_1a2cfecc27dc709b4dafc9b97245348f90" class="anchor"></a>

# class `USBStorage` <a id="class_u_s_b_storage" class="anchor"></a>

```
class USBStorage
  : public Arduino_UnifiedStorage
```

Represents a USB storage using the Arduino Unified Storage library.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`USBStorage`](#class_u_s_b_storage_1ad084f3bd2479b0a1daa88013f3cfe23a)`()` | Default constructor for the [USBStorage](#class_u_s_b_storage) class.
`public virtual int ` [`begin`](#class_u_s_b_storage_1a03f962b05deea5d39509af029d4898b9)`()` | Initializes the USB storage.
`public virtual int ` [`begin`](#class_u_s_b_storage_1a4512f903c687b7430382555c78b6e052)`(FileSystems fs)` | Initializes the USB storage with the specified file system.
`public virtual int ` [`unmount`](#class_u_s_b_storage_1a84413a1327d2a6b4c889a71c721ef4f3)`()` | Unmounts the USB storage.
`public virtual ` [`Folder`](#class_folder)` ` [`getRootFolder`](#class_u_s_b_storage_1a1d39336ddd7ec401dc2ed99c3117af59)`()` | Retrieves the root folder of the USB storage.
`public virtual int ` [`formatFAT`](#class_u_s_b_storage_1a12c7124a493cf587e5651314a9331ad5)`()` | Formats the USB storage with the FAT file system.
`public virtual int ` [`formatLittleFS`](#class_u_s_b_storage_1a1f5f3a6d258f4a327c2dd96331a66e30)`()` | Formats the USB storage with the LittleFS file system.
`public bool ` [`isConnected`](#class_u_s_b_storage_1a228919e4b7f6fe0619fbcb33da9a9534)`()` | Checks if the USB storage is connected.
`public bool ` [`isAvailable`](#class_u_s_b_storage_1ad71d15f8c9bcd12aa14a2bd6be620184)`()` | Checks if the USB storage is available.
`public void ` [`checkConnection`](#class_u_s_b_storage_1adf1432619e4e970d34f14742d6932dfe)`()` | Checks the USB storage connection status.
`private FileSystems ` [`fs`](#class_u_s_b_storage_1a65c532755dae77664016c63e3a69a6d6) | 
`private bool ` [`connected`](#class_u_s_b_storage_1abe6cfe6ed5e98e72c21150a6af17195c) | 
`private unsigned long ` [`previousMillis`](#class_u_s_b_storage_1a1421967255a94a2f4be67a5e37017307) | 
`private int ` [`interval`](#class_u_s_b_storage_1aecbd90e5183fd2dc86d98725d1577444) | 

## Members

### `public  ` [`USBStorage`](#class_u_s_b_storage_1ad084f3bd2479b0a1daa88013f3cfe23a)`()` <a id="class_u_s_b_storage_1ad084f3bd2479b0a1daa88013f3cfe23a" class="anchor"></a>

Default constructor for the [USBStorage](#class_u_s_b_storage) class.

### `public virtual int ` [`begin`](#class_u_s_b_storage_1a03f962b05deea5d39509af029d4898b9)`()` <a id="class_u_s_b_storage_1a03f962b05deea5d39509af029d4898b9" class="anchor"></a>

Initializes the USB storage.

#### Returns
1 if successful, 0 if failed.

### `public virtual int ` [`begin`](#class_u_s_b_storage_1a4512f903c687b7430382555c78b6e052)`(FileSystems fs)` <a id="class_u_s_b_storage_1a4512f903c687b7430382555c78b6e052" class="anchor"></a>

Initializes the USB storage with the specified file system.

#### Parameters
* `fs` The desired file system (FS_FAT or FS_LITTLEFS). 

#### Returns
1 if successful, 0 if failed.

### `public virtual int ` [`unmount`](#class_u_s_b_storage_1a84413a1327d2a6b4c889a71c721ef4f3)`()` <a id="class_u_s_b_storage_1a84413a1327d2a6b4c889a71c721ef4f3" class="anchor"></a>

Unmounts the USB storage.

#### Returns
1 if successful, 0 if failed.

### `public virtual ` [`Folder`](#class_folder)` ` [`getRootFolder`](#class_u_s_b_storage_1a1d39336ddd7ec401dc2ed99c3117af59)`()` <a id="class_u_s_b_storage_1a1d39336ddd7ec401dc2ed99c3117af59" class="anchor"></a>

Retrieves the root folder of the USB storage.

#### Returns
The root folder as a [Folder](#class_folder) object.

### `public virtual int ` [`formatFAT`](#class_u_s_b_storage_1a12c7124a493cf587e5651314a9331ad5)`()` <a id="class_u_s_b_storage_1a12c7124a493cf587e5651314a9331ad5" class="anchor"></a>

Formats the USB storage with the FAT file system.

#### Returns
1 if successful, 0 if failed.

### `public virtual int ` [`formatLittleFS`](#class_u_s_b_storage_1a1f5f3a6d258f4a327c2dd96331a66e30)`()` <a id="class_u_s_b_storage_1a1f5f3a6d258f4a327c2dd96331a66e30" class="anchor"></a>

Formats the USB storage with the LittleFS file system.

#### Returns
1 if successful, 0 if failed.

### `public bool ` [`isConnected`](#class_u_s_b_storage_1a228919e4b7f6fe0619fbcb33da9a9534)`()` <a id="class_u_s_b_storage_1a228919e4b7f6fe0619fbcb33da9a9534" class="anchor"></a>

Checks if the USB storage is connected.

#### Returns
true if connected, false otherwise.

### `public bool ` [`isAvailable`](#class_u_s_b_storage_1ad71d15f8c9bcd12aa14a2bd6be620184)`()` <a id="class_u_s_b_storage_1ad71d15f8c9bcd12aa14a2bd6be620184" class="anchor"></a>

Checks if the USB storage is available.

#### Returns
true if available, false otherwise.

### `public void ` [`checkConnection`](#class_u_s_b_storage_1adf1432619e4e970d34f14742d6932dfe)`()` <a id="class_u_s_b_storage_1adf1432619e4e970d34f14742d6932dfe" class="anchor"></a>

Checks the USB storage connection status.

### `private FileSystems ` [`fs`](#class_u_s_b_storage_1a65c532755dae77664016c63e3a69a6d6) <a id="class_u_s_b_storage_1a65c532755dae77664016c63e3a69a6d6" class="anchor"></a>

### `private bool ` [`connected`](#class_u_s_b_storage_1abe6cfe6ed5e98e72c21150a6af17195c) <a id="class_u_s_b_storage_1abe6cfe6ed5e98e72c21150a6af17195c" class="anchor"></a>

### `private unsigned long ` [`previousMillis`](#class_u_s_b_storage_1a1421967255a94a2f4be67a5e37017307) <a id="class_u_s_b_storage_1a1421967255a94a2f4be67a5e37017307" class="anchor"></a>

### `private int ` [`interval`](#class_u_s_b_storage_1aecbd90e5183fd2dc86d98725d1577444) <a id="class_u_s_b_storage_1aecbd90e5183fd2dc86d98725d1577444" class="anchor"></a>

Generated by [Moxygen](https://github.com/sourcey/moxygen)