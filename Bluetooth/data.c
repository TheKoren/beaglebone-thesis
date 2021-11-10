//
// Created by koren on 2021. 11. 06..
//

#include "data.h"

void controlprint()
{
    printf("TVOC: %d ppd\neCO2: %li ppm\nUV Index: %.0f\nAmb light: %.2f Lux\nTemp: %.2f °C\nHumidity: %.2f %%RH\nSound Level: %.2f dBA\n", control.TVOC,
           control.ECO2, control.UV, control.AMB, control.TEMP, control. HUM, control.SOUND);
}

void datalogging(const char * address)
{
    writeDataToFile(address);
    controlprint();
    printf("Successfully disconnected from the bluetooth device.\n");
}

void writeDataToFile(const char * address)
{
    FILE * fd = fopen("data.txt","ab");
    if(fd == NULL)
    {
        return;
    }
    fprintf(fd,"%s,%u,%d,%li,%.0f,%.2f,%.2f,%.2f,%.2f\n",address,(unsigned)time(NULL),control.TVOC, control.ECO2, control.UV, control.AMB, control.TEMP, control.HUM, control.SOUND);
}
