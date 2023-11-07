/*
    InternalStoragePartitioning

    This example demonstrates the usage of the "Arduino_UnifiedStorage" library for retrieving and creating partitions on the internal storage.
    The code should help you understand how to work with partitions and perform file operations in different partitions.

    It creates the partitions specified in the std::vector<Partitions> you find at the top of the sketch. 
    You can define your own, as long as the size of all partitions doesn't exceed the size of your board's QSPI flash( if you are in doubt about that check docs.arduino.com for more information) and as long as you don't have more than 4 partitions (MBR limitation)
    The Partition struct has two values:
        - `size` the size of your partition in kilobytes
        - 'fileSystemType` which can be either `FS_FAT` or `FS_LITTLEFS`

    Here are a few examples of valid partitioning schemes: 
        - std::vector<Partition> partitioningScheme  = {{16384, FS_FAT}};
        - std::vector<Partition> partitioningScheme  = {{2048, FS_FAT}, {6144, FS_FAT} {8192, FS_LITTLEFS}};
        - std::vector<Partition> partitioningScheme  = {{4096, FS_LITTLEFS}, {4096, FS_FAT}, {4096, FS_LITTLEFS}, {4096, FS_FAT}};

    The code defines the following main functions:
    1. `testWriting`: This function tests writing to a file in a specified storage partition by creating a file, writing data to it, reading the data, and then removing the file.
    2. `testAllPartitions`: This function tests all partitions in a list of partitions by creating an InternalStorage object for each partition, mounting it, and testing file operations within each partition.
    3. `listPartitions`: This function reads the MBR sector on the QSPI drive and retrieves the partitioning scheme, if this sketch is successful it should return exactly the partitioning scheme you created


    INSTRUCTIONS:
    1. Check compatibility with your board and make sure you have "POSIXStorage" and "Arduino_UnifiedStorage" installed
    2. Connect your board to the serial monitor
    3. Wait for the sketch to run 
    4. Modify the partitioning scheme according to your needs 

    Created: 26th October 2023
    By: Cristian Dragomir

*/

#include <Arduino_UnifiedStorage.h>
#include <vector>

// Create a vector of partitions with one partition of 16MB using LittleFS
std::vector<Partition> partitioningScheme  = {   
        {1024, FS_FAT}, // 1 MB for certificates
        {5120, FS_FAT}, // 5 MB for OTA firmware updates
        {8192, FS_LITTLEFS} // 8 MB for user data
};

// Function to test writing to a file in the specified storage partition
void testWriting(Arduino_UnifiedStorage *storage) {
    // Get the root folder of the storage
    Folder root = storage->getRootFolder();

    // Create a new file named "file.txt" for writing
    UFile file = root.createFile("file.txt", FileMode::WRITE);
    Serial.println("\t\t - File path: " + file.getPathAsString());
    
    // Write data to the file
    file.write("writing stuff to the file");

    // Change the file mode to READ for reading
    file.changeMode(FileMode::READ);
    Serial.println("\t\t - File contents: " + file.readAsString());
    file.close(); // Close the file
    file.remove(); // Remove the file
}

// Function to test all partitions in the provided list of partitions
void testAllPartitions(std::vector<Partition> partitions) {
    for (size_t i = 1; i < partitions.size() + 1; ++i) {
        const char *partitionName = createPartitionName(i);
        
        // Create an InternalStorage object for the partition
        InternalStorage thisPartition = InternalStorage(i, partitionName, partitions[i - 1].fileSystemType);

        // Check if the partition can be mounted
        if (thisPartition.begin()) {
            Serial.println("\t - Successfully mounted partition: /" + String(partitionName));
            Serial.println("\t - Testing file operations: ");
            testWriting(&thisPartition); // Test writing to a file in the partition
        }

        Serial.println();
    }
}


void listPartitions(){
    std::vector<Partition> partitions = InternalStorage::readPartitions();
    int partitionIndex = 0;
    for (auto partition : partitions) {
        partitionIndex ++;
        Serial.println("Partition " + String(partitionIndex));
        Serial.println("\t * Size: " + String(partition.size));
        Serial.println("\t * Type: " + prettyPrintFileSystemType(partition.fileSystemType));
        Serial.println();
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Arduino_UnifiedStorage::debuggingModeEnabled = false;

    // Partition the storage with the specified partitions
    bool partitioned = InternalStorage::partition(partitioningScheme);

    if(partitioned){
        Serial.println("Successfully partitioned the storage");
    } else {
        Serial.println("Failed to partition the storage, partition scheme probably invalid");
        Serial.println("Turn on logging to see more details");
    }
    // Test all partitions
    testAllPartitions(partitioningScheme);

    delay(1000);

    // Read the MBR sector and display the partitions 
    listPartitions();
}

void loop() {
    // Your main loop code (if any) can go here
}
