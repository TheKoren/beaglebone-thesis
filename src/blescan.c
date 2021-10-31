//
// Created by koren on 2021. 10. 14..
//

#include "blescan.h"


/* Global variables */

Config config;

char * uuids_str[NUM_OF_UUIDS] =
        {
            TVOC_UUID,
            ECO2_UUID,
            //BATTLVL_UUID,
            HALLFIELDSTATE_UUID,
            HALLFIELDSTRENGTH_UUID,
            //PRESSURE_UUID,
            UVINDEX_UUID,
            AMBLIGHT_UUID,
            TEMP_UUID,
            HUM_UUID,
            SOUNDLVL_UUID,
        };

char * mac_str[NUM_OF_MAC] =
        {
            SL_TB_0,
            SL_TB_1,
        };

/*Functions*/
void ble_handler(void)
{
    int i;
    int ret;
    const char* adapter_name;
    void* adapter;
    ret = gattlib_adapter_open(adapter_name, &adapter);
    for(i = 0; i < NUM_OF_UUIDS; i++)
    {
        gattlib_string_to_uuid(uuids_str[i],MAX_LEN_UUID_STR + 1,config.uuids[i]);
    }
    if(ret)
    {
        printf("Failed to open adapter.\n");
        return;
    }
    for(i = 0; i < NUM_OF_MAC; i++)
    {
        ble_connect_device(mac_str[i]);
    }
}

void ble_connect_device(char * address)
{
    gatt_connection_t* gatt_connection; // TODO: Understand
    gattlib_primary_service_t* services;
    gattlib_characteristic_t* characteristics;

    int ret, i, j;
    int services_count, characteristics_count;
    char uuid_str[MAX_LEN_UUID_STR + 1];

    printf("----------START %s ----------\n", address);
    gatt_connection = gattlib_connect(NULL, address, GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
    if(NULL == gatt_connection)
    {
        printf("Failed to connect to the bluetooth device.\n");
        return;
    }
    else
    {
        printf("Successfully connected to the bluetooth device.\n");
    }

    ret = gattlib_discover_primary(gatt_connection, &services, &services_count);
    if(0 != ret)
    {
        printf("Fail to discover primary services. \n");
        return;
    }

    for(i = 0; i < services_count; i++)
    {
        gattlib_uuid_to_string(&services[i].uuid, uuid_str, sizeof(uuid_str));

        printf("service[%d] start_handle:%02x end_handle:%02x uuid:%s\n", i, services[i].attr_handle_start, services[i].attr_handle_end, uuid_str);
    }
    free(services);

    ret = gattlib_discover_char(gatt_connection, &characteristics, &characteristics_count);
    if (0 != ret)
    {
        printf("Fail to discover characteristics.\n");
        return;
    }
    for (i = 0; i < characteristics_count; i++)
    {
        gattlib_uuid_to_string(&characteristics[i].uuid, uuid_str, sizeof(uuid_str));

        printf("characteristic[%d] properties: %02x value_handle:%04x uuid: %s\n", i, characteristics[i].properties, characteristics[i].value_handle, uuid_str);
    }

    uint8_t *buffer = NULL;
    size_t len;

    for(i = 0; i < NUM_OF_UUIDS; i++)
    {
        ret = gattlib_read_char_by_uuid(gatt_connection, config.uuids[i], (void**)&buffer, &len);
        if(ret != GATTLIB_SUCCESS)
        {
            gattlib_uuid_to_string(config.uuids[i], uuid_str, sizeof(uuid_str));
            printf("Could not read data from: %s.\n",uuid_str);
        }
        else
        {   printf("Read UUID completed: ");
            for(j = 0; j < len; j++)
            {
                printf("%02x ", buffer[j]);
            }
            printf("\n");
            switch(i)
            {
                case 0: decoder_TVOC();
                    break;
                case 1: decoder_ECO2();
                    break;
                case 2: decoder_HALLFIELDSTATE();
                    break;
                case 3: decoder_HALLFIELDSTRENGTH();
                    break;
                case 4: decoder_UVINDEX();
                    break;
                case 5: decoder_AMBLIGHT();
                    break;
                case 6: decoder_TEMP();
                    break;
                case 7: decoder_HUM();
                    break;
                case 8: decoder_SOUND();
                    break;
                default: /* Do nothing */
                    break;
            }
            free(buffer);
        }
    }
    free(characteristics);
    gattlib_disconnect(gatt_connection);
}

void decoder_TVOC()
{

}

void decoder_ECO2()
{

}

void decoder_HALLFIELDSTATE()
{

}

void decoder_HALLFIELDSTRENGTH()
{

}

void decoder_UVINDEX()
{

}

void decoder_AMBLIGHT()
{

}

void decoder_TEMP()
{

}

void decoder_HUM()
{

}

void decoder_SOUND()
{

}