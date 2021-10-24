//
// Created by koren on 2021. 10. 15..
//

#include "data.h"
#include "blescan.h"



bool get_address_from_config()
{
    bool ret = true;
    FILE *fd = fopen("mac.txt", "r");
    if (NULL == fd)
    {
        printf("No datafile found - mac.txt");
        ret = false;
    }
    int num = 0;
    char * buffer;
    while(NULL != fgets(buffer, BUFF_SIZE,fd))
    {
        config.address[num] = buffer;
        num = num + 1;
    }

    fclose(fd);
    config.num = num;

    if(0 == num)
    {
        ret = false;
    }

    return ret;
}
