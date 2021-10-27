//
// Created by koren on 2021. 10. 14..
//

#ifndef THESIS_BLESCAN_H
#define THESIS_BLESCAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include "gattlib.h"
#include "data.h"
#include <time.h>

#define NUM_OF_UUIDS 11u
#define NUM_OF_MAC 2u

/*UUID Descriptors*/
#define TVOC_UUID "efd658ae-c401-ef33-76e7-91b00019103b"

#define ECO2_UUID "efd658ae-c402-ef33-76e7-91b00019103b"

#define BATTLVL_UUID "00002a19-0000-1000-8000-00805f9b34fb"

#define HALLFIELDSTATE_UUID "f598dbc5-2f01-4ec5-9936-b3d1aa4f957f"

#define HALLFIELDSTRENGTH_UUID "f598dbc5-2f02-4ec5-9936-b3d1aa4f957f"

#define PRESSURE_UUID "00002902-0000-1000-8000-00805f9b34fb"

#define UVINDEX_UUID "00002a76-0000-1000-8000-00805f9b34fb"

#define AMBLIGHT_UUID "c8546913-bfd9-45eb-8dde-9f8754f4a32e"

#define TEMP_UUID "00002a6e-0000-1000-8000-00805f9b34fb"

#define HUM_UUID "00002a6f-0000-1000-8000-00805f9b34fb"

#define SOUNDLVL_UUID "c8546913-bf02-45eb-8dde-9f8754f4a32e"

/*-----------------*/

/*MAC*/

#define SL_TB_0 "14:B4:57:6D:A5:6D"
#define SL_TB_1 "00:0B:57:64:8F:DD"

typedef struct Config {
    uuid_t * uuids[NUM_OF_UUIDS];

}Config;

extern Config config;

void ble_handler(void);
void ble_connect_device(char * addresss);

#endif //THESIS_BLESCAN_H
