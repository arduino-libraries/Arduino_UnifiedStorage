   /*
    BackupInternalPartitions

    This code demonstrates how the "Arduino_UnifiedStorage" can be used to access multiple partitions on the internal storage,
    and transfer information to a USB Mass storage device.

    In the setup function, the code initializes Serial communication, and registers a callback for the insertion of the USB Drive. 
    
    If the device is successfully mounted, a folder for this instance of a backup will be created on the USB Drive.

    Afterwards the sketch does the following:
        - lists all partitions available on the InternalStorage
        - mounts each partition
        - creates a sub folder for each partition,
        - copies everything on that partition to the corresponding subfolder.
    
    The "addSomeFakeFiles" function generates random files in the specified folder, simulating real data.
    The "move" function is responsible for transferring folders and files between storage locations.

    INSTRUCTIONS
    - Make sure you have "POSIXStorage" and "Arduino_UnifiedStorage" installed
    - Insert a USB Drive whenever you want 
    - Wait for the sketch to finish, it will display the following "DONE, you can restart the board now" when successful
    - Unplug the USB device and inspect its contents. 

    Created: 31th August 2023
    By: Cristian Dragomir

    Source: https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/BackupInternalPartitions/BackupInternalPartitions.ino
*/

#include <Arduino_UnifiedStorage.h>


constexpr boolean createFakeFiles = true;
boolean done = false;
volatile boolean connected = false;

USBStorage thumbDrive;

void addSomeFakeFiles(Folder * folder){
    Arduino_UnifiedStorage::debugPrint("Adding some fake files to: " + String(folder -> getPathAsString()));

    for (int i = 0; i < random(0, 9); i++){
        UFile thisFile = folder -> createFile("File_"+ String(random(999)), FileMode::WRITE);
        Arduino_UnifiedStorage::debugPrint("\t * " + thisFile.getPathAsString());
        thisFile.write("writing stuff to the file");
        thisFile.close();
    }


    Folder subfolder = folder -> createSubfolder("ChildFolder_"+ String(random(999)));
    for (int i = 0; i < random(0, 9); i++){
        UFile thisFile = subfolder.createFile("File_"+ String(random(999)), FileMode::WRITE);
        Arduino_UnifiedStorage::debugPrint("\t * " + thisFile.getPathAsString());
        thisFile.write("writing stuff to the file");
        thisFile.close();
    }
}

void move(Folder * source, Folder * dest){
    for(Folder f: source -> getFolders()){
        Arduino_UnifiedStorage::debugPrint("Copying folder :" + String(f.getPathAsString()));
        f.moveTo(*dest);
    }

    for(UFile f: source -> getFiles()){
        Arduino_UnifiedStorage::debugPrint("Copying file :" + String(f.getPathAsString()));
        f.moveTo(*dest);
    }
}


void setup(){
    randomSeed(analogRead(A0));

#if !defined(ARDUINO_OPTA)
    Serial.begin(115200);
    while(!Serial);
#else
    beginRS485(115200);
#endif

    // toggle this to enable debugging output
    Arduino_UnifiedStorage::debuggingModeEnabled = true;

    bool thumbMounted = thumbDrive.begin(FS_FAT);
    if(thumbMounted){
        Arduino_UnifiedStorage::debugPrint("USB Thumb Drive has been mounted");

        Folder thumbRoot = thumbDrive.getRootFolder();
        String folderName = "InternalBackup_" + String(millis());
        Arduino_UnifiedStorage::debugPrint(folderName);
        Folder backupFolder = thumbRoot.createSubfolder(folderName);

        int partitionIndex = 0;

        std::vector<Partition> partitions = InternalStorage::readPartitions();
        Arduino_UnifiedStorage::debugPrint("Found " + String(partitions.size()) + " partitions on internalStorage \n");

        for (auto part: partitions){
            partitionIndex++;
            const char * partitionName = createPartitionName(partitionIndex);
            Folder thisPartitionBackupFolder = backupFolder.createSubfolder(partitionName);

            InternalStorage thisPartition = InternalStorage(partitionIndex, partitionName, part.fileSystemType);
            thisPartition.begin();

            Folder partitionRootFolder = thisPartition.getRootFolder();
            Arduino_UnifiedStorage::debugPrint(partitionRootFolder.getPathAsString());

            if(createFakeFiles){
                addSomeFakeFiles(&partitionRootFolder);
            }

            move(&partitionRootFolder, &thisPartitionBackupFolder);
            thisPartition.unmount();
        }

        thumbDrive.unmount();
    
        Arduino_UnifiedStorage::debugPrint("DONE, you can restart the board now");
    }
}

void loop(){
}
