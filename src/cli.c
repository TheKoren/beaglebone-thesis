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
    int opt = 0;

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
        }
    }
}

void cli_caseHelp(void)
{
    printf(CLI_HELP_MESSAGE);
    exit(EXIT_SUCCESS);
}
void cli_caseMeasure(void)
{
    // Call gatttool functionalites
    ble_handler();
}
void cli_caseDeleteData(void)
{
    // data.h, data.c, config
}
