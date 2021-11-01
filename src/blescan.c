//
// Created by koren on 2021. 10. 14..
//

#include "blescan.h"


/* Global variables */

Control control;

char * uuids_str[NUM_OF_UUIDS] =
        {
            TVOC_UUID,
            ECO2_UUID,
            //BATTLVL_UUID,
            //HALLFIELDSTATE_UUID,
            //HALLFIELDSTRENGTH_UUID,
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
        gattlib_string_to_uuid(uuids_str[i],MAX_LEN_UUID_STR + 1, control.uuids[i]);
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
    gatt_connection_t* gatt_connection;
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
        ret = gattlib_read_char_by_uuid(gatt_connection, control.uuids[i], (void**)&buffer, &len);
        if(ret != GATTLIB_SUCCESS)
        {
            gattlib_uuid_to_string(control.uuids[i], uuid_str, sizeof(uuid_str));
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
                case 0: decoder_TVOC(buffer, len);
                    break;
                case 1: decoder_ECO2(buffer, len);
                    break;
                case 2: decoder_UVINDEX(buffer, len);
                    break;
                case 3: decoder_AMBLIGHT(buffer, len);
                    break;
                case 4: decoder_TEMP(buffer, len);
                    break;
                case 5: decoder_HUM(buffer, len);
                    break;
                case 6: decoder_SOUND(buffer, len);
                    break;
                default: /* Do nothing */
                    break;
            }
            free(buffer);
        }
    }
    free(characteristics);
    gattlib_disconnect(gatt_connection);

    controlprint();
}

uint32_t pow(uint8_t base, uint8_t power)
{
    uint32_t result = 1;
    for (int i = 1; i <= power; i++)
    {
        result *= base;
    }
    return result;
}

void decoder_TVOC(const uint8_t * buffer, size_t len)
{
    uint16_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint16_t)buffer[i] * pow(16,j);
        j = j + 2;
    }
    control.TVOC = sum;
}

void decoder_ECO2(const uint8_t * buffer, size_t len)
{
    uint16_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint16_t)buffer[i] * pow(16,j);
        j = j + 2;
    }
    control.ECO2  = sum;
}

void decoder_UVINDEX(const uint8_t * buffer, size_t len)
{
    uint8_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint8_t)buffer[i] * pow(16,j);
        j = j + 2;
    }
    control.UV = sum;
}

void decoder_AMBLIGHT(const uint8_t * buffer, size_t len)
{
    uint32_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint32_t)buffer[i] * pow(16,j);
        j = j + 2;
    }
    control.AMB = sum;
}

void decoder_TEMP(const uint8_t * buffer, size_t len)
{
    uint16_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint16_t)buffer[i] * pow(16,j);
        j = j + 2;
    }
    control.TEMP = sum;
}

void decoder_HUM(const uint8_t * buffer, size_t len)
{
    uint16_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint16_t)buffer[i] * pow(16,j);
        j = j + 2;
    }
    control.HUM = sum;
}

void decoder_SOUND(const uint8_t * buffer, size_t len)
{
    uint16_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint16_t)buffer[i] * pow(16,j);
        j = j + 2;
    }
    control.SOUND = sum;
}

void controlprint()
{
    printf("=== Values from ThunderBoard ===\n\n");
    printf("TVOC: %02x\nECO2: %02x\nUV: %02x\nAMB: %02x\nTEMP: %02x\nHUM: %02x\nSOUND: %02x\n", control.TVOC,
                                    control.ECO2, control.UV, control.AMB, control.TEMP, control. HUM, control.SOUND);
}