//
// Created by koren on 2021. 10. 08..
//

#include "cli.h"
#include "blescan.h"

#define CLI_HELP_MESSAGE "Air Quality Assessment IoT Application\n\n \
Options:\n \
\t  -h ........... This help message. \n \
\t  -m ........... Start measurement. \n \
\t  -d ........... Delete all measurement data. \n \
\n"

int commandInterpreter(int argc, char *const *argv)
{
    int opt;
    while((opt = getopt(argc,argv, "hmd")) != -1)
    {
        switch(opt)
        {
            case 'h':
                cli_caseHelp();
                break;
            case 'm':
                cli_caseMeasure();
                break;
            case 'd':
                cli_caseDeleteData();
                break;
            default:
                return -1;
        }
    }
    return 1;
}

void cli_caseHelp(void)
{
    printf(CLI_HELP_MESSAGE);
    exit(EXIT_SUCCESS);
}
void cli_caseMeasure(void)
{
    ble_handler();
    exit(EXIT_SUCCESS);
}
void cli_caseDeleteData(void)
{
    deleteData();
    exit(EXIT_SUCCESS);
}
