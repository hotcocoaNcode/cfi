//
// Created by Ethan Lee on 9/21/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "jlog.h"

int logLevel = 0;

void jLog(char description[]){
    if (logLevel > 1){
        printf("%s%s%s\n", ANSI_WHITE, description, ANSI_RESET);
    }
}

void jImportantPurple(char description[]){
    printf("%s%s%s\n", ANSI_PURPLE, description, ANSI_RESET);
}

void jImportantGreen(char description[]){
    printf("%s%s%s\n", ANSI_GREEN, description, ANSI_RESET);
}

void jImportantNormal(char description[]){
    printf("%s%s\n", ANSI_RESET, description);
}

void jWarn(char description[]){
    if (logLevel > 0){
        printf("%sWarning: %s%s\n", ANSI_YELLOW, description, ANSI_RESET);
    }
}

void jError(char description[]){
    printf("%sError: %s%s\n", ANSI_RED, description, ANSI_RESET);
}

void jFatal(char description[]){
    printf("%sFatal Error: %s%s\n", ANSI_RED, description, ANSI_RESET);
    exit(1);
}