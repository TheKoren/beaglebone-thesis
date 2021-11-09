//
// Created by koren on 2021. 11. 06..
//

#include "data.h"

void datalogging(const char * address)
{
    writeDataToFile(address);
}

void writeDataToFile(const char * address)
{
    FILE * fd = fopen("data.txt","ab");
    if(fd == NULL)
    {
        return;
    }
    fprintf(fd,"%s,%u,%d,%li,%f,%f,%f,%f,%f\n",address,(unsigned)time(NULL),control.TVOC, control.ECO2, control.UV, control.AMB, control.TEMP, control.HUM, control.SOUND);
}
