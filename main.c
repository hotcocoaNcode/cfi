#include "jlog.h"
#include "interpretModes.h"

#include <stdlib.h>
#include <stdio.h>

long fileLength = -1;

char *readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL) return NULL; //could not open file
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(fileLength);

    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }

    code[n] = '\0';

    return code;
}

int exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // "I love Kagurabachi. I wanna kagura his bachi if you know what I mean"
    // - Shu, 2023 (while i was writing this)

    if (argc != 2) jFatal("cfi requires exactly 1 argument (file name)!");
    if (!exists(argv[1])) jFatal("File does not exist!");
    char *file = readFile(argv[1]);

    int b1 = file[0] & 0xff; //Byte1
    int b2 = file[1] & 0xff; //Byte2
    int b3 = file[2] & 0xff; //Byte3
    int isValidFluffBytecode =
            b1 == 0xf1 && b2 == 0x00 && b3 == 0xf1; //F1OOF1 (Floofi) 3-byte Magic Number check
    if (!isValidFluffBytecode) jFatal("Non-valid bytecode!");
    int headerSize = (unsigned char) file[3];
    int bytecodeRevision = (unsigned char) file[7];
    //Skip over header and access bytecode through vector later
    char *bytecode = file + headerSize;

    switch (bytecodeRevision){
        case (0): // 1 and 0 are both rev 1 because I messed up versioning
        case (1): {
            interpret_r1(bytecode, fileLength - headerSize);
            break;
        }
        default: {
            printf("%s\nFatal Error: Unknown bytecode version %d!", ANSI_RED, bytecodeRevision);
            exit(1);
        }
    }

    return 0;
}
