

#if defined()
QSPIFBlockDevice root(QSPI_SO0, QSPI_SO1, QSPI_SO2, QSPI_SO3,  QSPI_SCK, QSPI_CS, QSPIF_POLARITY_MODE_1, 40000000);
mbed::MBRBlockDevice wifi_data(&root, 1);
mbed::MBRBlockDevice ota_data(&root, 2);
mbed::MBRBlockDevice user_data(&root, 3);


void setup(){
    
}