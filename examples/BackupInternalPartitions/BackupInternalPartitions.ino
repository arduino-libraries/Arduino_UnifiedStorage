   /*
   BackupInternalPartitions

   This code demonstrates how the "Arduino_UnifiedStorage" can be used to access multiple partitions on the internal storage,
   and transfer information to a USB Mass storage device.

   In the setup function, the code initializes serial communication, mounts both USB & internal storage.
   It then creates a root directory in the internal storage and creates a subdirectory with files inside it.

   The "addSomeFakeFiles" function generates random files in the specified folder, simulating real data.

   Afterward, it copies files from internal storage to USB storage and moves folders from each partition internal storage to USB storage.

   The "move" function is responsible for transferring folders and files between storage locations.

   The "backupPartitionsC33" and "backupPartitionsH7" functions backup partitions based on the board type, as each have a different default scheme. 

   Created: 31th August 2023
   By: Cristian Dragomir

   Source: https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/BackupInternalPartitions/BackupInternalPartitions.ino
*/

#include <Arduino_UnifiedStorage.h>


#if defined(ARDUINO_PORTENTA_C33)
InternalStorage ota = InternalStorage(1, "ota", FS_FAT);
InternalStorage data = InternalStorage(2, "data", FS_FAT);

#elif defined(ARDUINO_PORTENTA_H7_M7)
InternalStorage wifi = InternalStorage(1, "wifi", FS_FAT);
InternalStorage ota = InternalStorage(2, "ota", FS_FAT);
InternalStorage data = InternalStorage(3, "data", FS_FAT);
#endif

USBStorage thumbDrive = USBStorage();


void addSomeFakeFiles(Folder * folder){
    Serial.println("* adding some fake files to: " + String(folder -> getPathAsString()));

    for (int i = 0; i < random(0, 9); i++){
        UFile thisFile = folder -> createFile("File_"+ String(random(999)), FileMode::WRITE);
        Serial.println("\t * " + thisFile.getPathAsString());
        thisFile.write("writing stuff to the file");
        thisFile.close();
    }


    Folder subfolder = folder -> createSubfolder("ChildFolder_"+ String(random(999)));
    for (int i = 0; i < random(0, 9); i++){
        UFile thisFile = subfolder.createFile("File_"+ String(random(999)), FileMode::WRITE);
        Serial.println("\t * " + thisFile.getPathAsString());
        thisFile.write("writing stuff to the file");
        thisFile.close();
    }
}

void move(Folder * source, Folder * dest){
    for(Folder f: source -> getFolders()){
        Serial.println("* copying folder :" + String(f.getPathAsString()));
        f.moveTo(*dest);
    }

    for(UFile f: source -> getFiles()){
        Serial.println("* copying file :" + String(f.getPathAsString()));
        f.moveTo(*dest);
    }
}





void backupPartitions(){
        Folder otaRoot = ota.getRootFolder();
        addSomeFakeFiles(&otaRoot);
        Folder otaFolder = backupFolder -> createSubfolder("ota");
        move(&otaRoot, &otaFolder);
        ota.unmount();
    } else {
        Serial.println("OTA partition not mounted, cannot proceed");
    }
}

void setup(){
    randomSeed(analogRead(A0));


    Serial.begin(115200);
    while(!Serial);

    int thumbMounted = thumbDrive.begin(FS_FAT);
    Serial.println("* usb drive mounted:" + String(thumbMounted));


    Folder thumbRoot = thumbDrive.getRootFolder();
    String folderName = "InternalBackup_" + String(millis());
    Folder backupFolder = thumbRoot.createSubfolder(folderName);

    int partitionIndex = 0;
    for (auto part: InternalStorage::readPartitions()){
        partitionBackupFolderName = "Part" + String(partitionIndex);
        backupFolder.createFolder(partitionBackupFolderName);
        
        
    }

    thumbDrive.unmount();

    Serial.println("DONE, you can restart the board now");

}


void loop(){

}
