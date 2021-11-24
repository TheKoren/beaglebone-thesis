//
// Created by koren on 2021. 11. 06..
//

#ifndef BEAGLEBONE_DATA_H
#define BEAGLEBONE_DATA_H

#include "blescan.h"

void datalogging(const char * address);
void writeDataToFile(const char * address, bool isDataValid);
void controlprint(void);
void badConnectionDataLogging(const char * address);


#endif //BEAGLEBONE_DATA_H
