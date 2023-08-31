

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
    Serial.println("* adding some fake files to: " + String(folder -> getPathString()));

    for (int i = 0; i < random(0, 9); i++){
        UFile thisFile = folder -> createFile("File_"+ String(random(999)), FileMode::WRITE);
        Serial.println("\t * " + thisFile.getPathString());
        thisFile.write("writing stuff to the file");
        thisFile.close();
    }


    Folder subfolder = folder -> createSubfolder("ChildFolder_"+ String(random(999)));
    for (int i = 0; i < random(0, 9); i++){
        UFile thisFile = subfolder.createFile("File_"+ String(random(999)), FileMode::WRITE);
        Serial.println("\t * " + thisFile.getPathString());
        thisFile.write("writing stuff to the file");
        thisFile.close();
    }
}

void move(Folder * source, Folder * dest){
    for(Folder f: source -> getFolders()){
        Serial.println("* copying folder :" + String(f.getPathString()));
        f.moveTo(*dest);
    }

    for(UFile f: source -> getFiles()){
        Serial.println("* copying file :" + String(f.getPathString()));
        f.moveTo(*dest);
    }
}


#if defined(ARDUINO_PORTENTA_C33)
void backupPartitionsC33(Folder * backupFolder){

    Serial.println("* backup location: " + String(backupFolder -> getPathString()));

    int otaMounted = ota.begin(FS_FAT);
    Serial.println("* ota partition mount: " + String(otaMounted));

    int dataMounted = data.begin(FS_FAT);
    Serial.println("* data partition mount: " + String(dataMounted));


    if(otaMounted == 1){
        Folder otaRoot = ota.getRootFolder();
        addSomeFakeFiles(&otaRoot);
        Folder otaFolder = backupFolder -> createSubfolder("ota");
        move(&otaRoot, &otaFolder);
        ota.unmount();
    } else {
        Serial.println("OTA partition not mounted, cannot proceed");
    }


    if(dataMounted == 1){
        Folder dataRoot = data.getRootFolder();
        addSomeFakeFiles(&dataRoot); 
        Folder dataFolder = backupFolder -> createSubfolder("data");
        move(&dataRoot, &dataFolder);
        data.unmount();
    } else {
        Serial.println("Data partition not mounted, cannot proceed");
    }
}
#endif 


#if defined(ARDUINO_PORTENTA_H7_M7)
void backupPartitionsH7(Folder * backupFolder){
    Serial.println("* backup location: " + String(backupFolder -> getPathString()));

    int wifiMounted = wifi.begin(FS_FAT);
    Serial.println("* wifi partition mount: " + String(wifiMounted));

    int otaMounted = ota.begin(FS_FAT);
    Serial.println("* ota partition mount: " + String(otaMounted));

    int dataMounted = data.begin(FS_FAT);
    Serial.println("* data partition mounted: " + String(dataMounted));

    if(wifiMounted == 1){
        Folder wifiRoot = wifi.getRootFolder();
        addSomeFakeFiles(&wifiRoot);
        Folder wifiFolder = backupFolder -> createSubfolder("wifi");
        move(&wifiRoot, &wifiFolder);
        wifi.unmount();
    } else {
        Serial.println("WiFi partition not mounted, cannot proceed");
    }

    if(otaMounted == 1){
        Folder otaRoot = ota.getRootFolder();
        addSomeFakeFiles(&otaRoot);
        Folder otaFolder = backupFolder -> createSubfolder("ota");
        move(&otaRoot, &otaFolder);
        ota.unmount();
    } else {
        Serial.println("OTA partition not mounted, cannot proceed");
    }


    if(dataMounted == 1){
        Folder dataRoot = data.getRootFolder();
        addSomeFakeFiles(&dataRoot); 
        Folder dataFolder = backupFolder -> createSubfolder("data");
        move(&dataRoot, &dataFolder);
        data.unmount();
    } else {
        Serial.println("Data partition not mounted, cannot proceed");
    }
}
#endif 

void setup(){
    randomSeed(analogRead(A0));


    Serial.begin(115200);
    while(!Serial);

    int thumbMounted = thumbDrive.begin(FS_FAT);
    Serial.println("* usb drive mounted:" + String(thumbMounted));


    Folder thumbRoot = thumbDrive.getRootFolder();
    String folderName = "InternalBackup_" + String(millis());
    Folder backupFolder = thumbRoot.createSubfolder(folderName);


    #if defined(ARDUINO_PORTENTA_H7_M7)
        backupPartitionsH7(&backupFolder);
    #elif defined(ARDUINO_PORTENTA_C33)
        backupPartitionsC33(&backupFolder);
    #endif

    thumbDrive.unmount();

    Serial.println("DONE, you can restart the board now");

}


void loop(){

}
