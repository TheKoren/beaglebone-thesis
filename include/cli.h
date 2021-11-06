//
// Created by koren on 2021. 10. 08..
//

#ifndef THESIS_CLI_H
#define THESIS_CLI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

int commandInterpreter(int argc, char *const *argv);

/*CLI FUNCTION CASE DECLARATIONS*/

void cli_caseHelp (void) ;
void cli_caseMeasure(void);
void cli_caseDeleteData(void);

#endif //THESIS_CLI_H
