//
// Created by Ethan Lee on 9/21/23.
//

#ifndef FVM_ARM64_JLOG_H
#define FVM_ARM64_JLOG_H

#define ANSI_RESET "\e[0m"
#define ANSI_BLACK "\e[30m"
#define ANSI_RED "\e[31m"
#define ANSI_GREEN "\e[32m"
#define ANSI_YELLOW "\e[33m"
#define ANSI_BLUE "\e[34m"
#define ANSI_PURPLE "\e[35m"
#define ANSI_CYAN "\e[36m"
#define ANSI_WHITE "\e[37m"

int logLevel;

void jLog(char description[]);

void jImportantPurple(char description[]);

void jImportantGreen(char description[]);

void jImportantNormal(char description[]);

void jWarn(char description[]);

void jError(char description[]);

void jFatal(char description[]);

#endif //FVM_ARM64_JLOG_H