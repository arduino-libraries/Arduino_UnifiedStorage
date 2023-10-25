#include <Arduino_UnifiedStorage.h>
#include <vector>

      

void testWriting(Arduino_UnifiedStorage * storage){
    Folder root = storage->getRootFolder();

    UFile file = root.createFile("file.txt", FileMode::WRITE);
    Serial.println("\t\t - File path: " + file.getPathAsString());
    file.write("writing stuff to the file");
    file.changeMode(FileMode::READ);
    Serial.println("\t\t - File contents: " + file.readAsString());
    file.close();
    file.remove();
}

const char* createPartitionName(int i) {
    switch(i){
        case 1: return "uno";
        case 2: return "due";
        case 3: return "tre";
        case 4: return "quattro";
        default: return "";
    }
}

void testAllPartitions(std::vector<Partition> partitions){
    for (size_t i = 1; i < partitions.size() + 1; ++i) {
        const char * partitionName = createPartitionName(i);    
        InternalStorage thisPartition = InternalStorage(i, partitionName, partitions[i - 1].fileSystem);
        if(thisPartition.begin()){
            Serial.println("\t - Succesfully mounted partition: /" + String(partitionName));
            Serial.println("\t - Testing file opperations: ");
            testWriting(&thisPartition);

        }

        Serial.println();
    }
}

void setup(){



    Serial.begin(115200);
    while(!Serial);


    Serial.println("Creating one partition of 16MB: ");
    std::vector<Partition> onePartition = {{8192, FS_LITTLEFS}};
    InternalStorage::partition(onePartition);
    testAllPartitions(onePartition);
    delay(5000);


    std::vector<Partition> partitions = InternalStorage::readPartitions();
    for(auto p: partitions){
        Serial.println("partition size: " + String(p.size));
        Serial.println("partition type: " + String(p.fileSystem));
        Serial.println();
    }
  
}

void loop(){
}