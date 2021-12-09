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
    writeDataToFile(address, true);
    controlprint();
    printf("Successfully disconnected from the bluetooth device.\n");
}

void badConnectionDataLogging(const char * address)
{
    writeDataToFile(address, false);
    printf("TVOC: NaN ppd\neCO2: NaN ppm\nUV Index: NaN\nAmb light: NaN Lux\nTemp: NaN °C\nHumidity: NaN %%RH\nSound Level: NaN dBA\n");
    printf("Bad data handled successfully\n");
}

void writeDataToFile(const char * address, bool isDataValid)
{
    FILE * fd = fopen("data.txt","ab");
    if(fd == NULL)
    {
        return;
    }
    if(isDataValid == true)
    {
        fprintf(fd,"%s,%u,%d,%li,%.0f,%.2f,%.2f,%.2f,%.2f\n",address,(unsigned)time(NULL),control.TVOC, control.ECO2, control.UV, control.AMB, control.TEMP, control.HUM, control.SOUND);
    }
    else
    {
        fprintf(fd,"%s,%u,NaN,NaN,NaN,NaN,NaN,NaN,NaN\n",address,(unsigned)time(NULL));
    }
}

void deleteData(void)
{
    FILE * fd = fopen("data.txt", "w");
    if(fd == NULL)
    {
        return;
    }
    else
    {
        printf("Successfully deleted the contents of data.txt file");
    }
    return;
}