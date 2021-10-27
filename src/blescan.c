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
                BATTLVL_UUID,
                HALLFIELDSTATE_UUID,
                HALLFIELDSTRENGTH_UUID,
                PRESSURE_UUID,
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

    for(i = 0; i < NUM_OF_UUIDS; i++)
    {
        gattlib_string_to_uuid(uuids_str[i],strlen(uuids_str[i]) + 1,config.uuids[i]);
    }

    uint32_t *buffer = NULL;
    size_t len = sizeof(uint32_t);
    for(i = 0; i < NUM_OF_UUIDS; i++)
    {
        ret = gattlib_read_char_by_uuid(gatt_connection, config.uuids[i], (void**)&buffer, &len);
        if(ret != GATTLIB_SUCCESS)
        {
            printf("UUID not found\n");
        }
        for(j; j < len; j++)
        {
            printf("%02x ", buffer[j]);
        }
        printf("\n");
    }
    // TODO: Handle buffer value.
    free(characteristics);
    gattlib_disconnect(gatt_connection);


}

