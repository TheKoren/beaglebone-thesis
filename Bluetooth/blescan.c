//
// Created by koren on 2021. 10. 14..
//

#include "blescan.h"


/* Global variables */

Control control;

long int value_data;
static uuid_t g_uuid;

char * uuids_str[NUM_OF_UUIDS] =
        {
            //BATTLVL_UUID,
            //HALLFIELDSTATE_UUID,
            //HALLFIELDSTRENGTH_UUID,
            //PRESSURE_UUID,
            HUM_UUID,
            SOUNDLVL_UUID,
            UVINDEX_UUID,
            AMBLIGHT_UUID,
            TEMP_UUID,
            ECO2_UUID,
            TVOC_UUID,
        };

char * mac_str[NUM_OF_MAC] =
        {
            SL_TB_0,
            SL_TB_1,
            SL_TB_2,
            SL_TB_3,
            SL_TB_4
        };

/*Functions*/
void ble_handler(void)
{
    int i;
    for(i = 0; i < NUM_OF_UUIDS; i++)
    {
        gattlib_string_to_uuid(uuids_str[i],MAX_LEN_UUID_STR + 1, control.uuids[i]);
    }
    for(i = 0; i < NUM_OF_MAC; i++)
    {
        ble_connect_device(mac_str[i]);
    }
}

void ble_connect_device(char * address) {
    gatt_connection_t *gatt_connection;
    int ret, i;
    int debounce = 1;
    char uuid_str[MAX_LEN_UUID_STR + 1];
    printf("---------- START %s ----------\n", address);
    gatt_connection = gattlib_connect(NULL, address, GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
    if (NULL == gatt_connection)
    {
        do{
            printf("Attempting connection %d times.\n", debounce);
            gatt_connection = gattlib_connect(NULL, address, GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
            debounce++;
        }while((debounce < 3) && (NULL == gatt_connection));

        if (NULL == gatt_connection)
        {
            printf("Failed to connect to the bluetooth device.\n");
            badConnectionDataLogging(address);
            return;
        }
    }
    printf("Successfully connected to the bluetooth device.\n");

    uint8_t *buffer = NULL;
    size_t len;

    for (i = 0; i < NUM_OF_UUIDS; i++) {
        ret = gattlib_read_char_by_uuid(gatt_connection, control.uuids[i], (void **) &buffer, &len);
        if (ret != GATTLIB_SUCCESS) {
            gattlib_uuid_to_string(control.uuids[i], uuid_str, sizeof(uuid_str));
            printf("Could not read data from: %s.\n", uuid_str);
        } else {
            switch (i) {
                case 0:
                    decoder_HUM(buffer, len);
                    break;
                case 1:
                    decoder_SOUND(buffer, len);
                    break;
                case 2:
                    decoder_UVINDEX(buffer, len);
                    break;
                case 3:
                    decoder_AMBLIGHT(buffer, len);
                    break;
                case 4:
                    decoder_TEMP(buffer, len);
                    break;
                case 5:
                    decoder_ECO2(buffer, len);
                    char * str;
                    if(control.ECO2 < 600)
                    {
                        str = GREEN;
                    }
                    else if((600 <= control.ECO2) && (control.ECO2 < 2000))
                    {
                        str = YELLOW;
                    }
                    else
                    {
                        str = RED;
                    }
                    gattlib_string_to_uuid(LED_UUID, MAX_LEN_UUID_STR+1, &g_uuid);
                    if ((strlen(str) >= 2) && (str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
                        value_data = strtol(str, NULL, 16);
                    } else {
                        value_data = strtol(str, NULL, 0);
                    }
                    ret = gattlib_write_char_by_uuid(gatt_connection, &g_uuid, &value_data, sizeof(value_data));
                    if(ret != GATTLIB_SUCCESS)
                    {
                        if (ret == GATTLIB_NOT_FOUND)
                        {
                            printf("Could not find GATT Characteristic with UUID %s", LED_UUID);
                        }
                        else
                        {
                            printf("Error while writing GATT Characteristic with UUID %s", LED_UUID);
                        }
                    }
                    break;
                case 6:
                    decoder_TVOC(buffer, len);
                    break;
                default: /* Do nothing */
                    break;
            }
            free(buffer);
        }
    }
    if(GATTLIB_SUCCESS != gattlib_disconnect(gatt_connection)){
        gattlib_disconnect(gatt_connection);
    }
    datalogging(address);

}

uint32_t power_on_number(uint8_t base, uint8_t power)
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
        sum = sum + (uint16_t)buffer[i] * power_on_number(16, j);
        j = j + 2;
    }
    control.TVOC = (int)sum;
}

void decoder_ECO2(const uint8_t * buffer, size_t len)
{
    uint16_t sum;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + ((uint16_t)buffer[i] * power_on_number(16, j));
        j = j + 2;
    }
    control.ECO2  = (long int)sum;
}

void decoder_UVINDEX(const uint8_t * buffer, size_t len)
{
    uint8_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint8_t)buffer[i] * power_on_number(16, j);
        j = j + 2;
    }
    control.UV = (double)sum;
}

void decoder_AMBLIGHT(const uint8_t * buffer, size_t len)
{
    uint32_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint32_t)buffer[i] * power_on_number(16, j);
        j = j + 2;
    }
    control.AMB = (double)sum / 100;
}

void decoder_TEMP(const uint8_t * buffer, size_t len)
{
    uint16_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint16_t)buffer[i] * power_on_number(16, j);
        j = j + 2;
    }
    control.TEMP = (double)sum / 100;
}

void decoder_HUM(const uint8_t * buffer, size_t len)
{
    uint16_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint16_t)buffer[i] * power_on_number(16, j);
        j = j + 2;
    }
    control.HUM = (double)sum / 100;
}

void decoder_SOUND(const uint8_t * buffer, size_t len)
{
    uint16_t sum = 0;
    uint8_t j = 0;
    for(int i = 0; i < len; i++)
    {
        sum = sum + (uint16_t)buffer[i] * power_on_number(16, j);
        j = j + 2;
    }
    control.SOUND = (double)sum / 100;
}

