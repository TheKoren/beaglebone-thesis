#include "cli.h"

int main(int argc, char** argv) {
    if(PROGRAM_FAILURE == (commandInterpreter(argc, argv))
    {
        printf("Error: Failed to interpret the command. Try -h for help\n");
    }
    return 0;
}
