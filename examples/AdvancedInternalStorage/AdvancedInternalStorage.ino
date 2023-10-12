#include <Arduino.h>
#include <Arduino_UnifiedStorage.h>
#include <vector>

      

void testWriting(Arduino_UnifiedStorage * storage){
    Folder root = storage->getRootFolder();
    UFile file = root.createFile("file.txt", FileMode::WRITE);
    file.write("writing stuff to the file");
    file.changeMode(FileMode::READ);
    Serial.println("Reading from file: " + file.readAsString());
    file.close();
    file.remove();
}

const char* createPartitionName(int i) {
    char buffer[20];  // Adjust the size accordingly
    snprintf(buffer, sizeof(buffer), "Part%d", i);
    return buffer;
}

void testAllPartitions(std::vector<Partition> partitions){
    for (size_t i = 1; i < partitions.size() + 1; ++i) {
        const char * partitionName = createPartitionName(i);
        
        InternalStorage thisPartition = InternalStorage(i, partitionName, partitions[i - 1].fs);
        if(thisPartition.begin()){
            Serial.println("Succesfully initialised partition: " + String(partitionName));
            testWriting(&thisPartition);
        }
    }
}

void setup(){



    Serial.begin(115200);
    while(!Serial);

    std::vector<Partition> onePartition = {{16384, FS_LITTLEFS}};
    InternalStorage::partition(onePartition);
    testAllPartitions(onePartition);
    delay(5000);


    std::vector<Partition> fourPartitions = {{4096, FS_LITTLEFS}, {4096, FS_LITTLEFS}, {4096, FS_LITTLEFS}, {4096, FS_LITTLEFS}};
    InternalStorage::partition(fourPartitions);
    testAllPartitions(fourPartitions);
    delay(5000);
  
}

void loop(){


}