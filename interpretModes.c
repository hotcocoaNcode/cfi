//
// Created by Ethan Lee on 10/1/23.
//

#include "interpretModes.h"
#include "jlog.h"
#include <stdio.h>
#include <stdlib.h>

void interpret_r1(char* bytecode, unsigned int length){
    char ram[16382]; //ram as a char vector
    short opstack[255]; //fixed-size stack with vector
    unsigned short opstack_head = 0; //Operator Stack head (stack but with fixed size cause yeah)
    for (int i = 0; i < length; i++){
        if (opstack_head > 255) {
            jFatal("Operator stack overflow!");
        }
        switch ((unsigned char) bytecode[i]) {
            case (0): { //Exit
                i++;
                char code = (signed char) (unsigned char) bytecode[i];
                exit(code);
            }

            case (60): {
                printf("CFluff does not support alternate interpreter modes!");
                exit(1);
            }

            case (2): {
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                int pointerAddress = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                i++;
                lo = (unsigned char) bytecode[i];
                i++;
                hi = (unsigned char) bytecode[i];
                int addressFrom = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                lo = (unsigned char) ram[pointerAddress];
                hi = (unsigned char) ram[pointerAddress+1];
                int addressTo = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                i++;
                lo = (unsigned char) bytecode[i];
                i++;
                hi = (unsigned char) bytecode[i];
                int offset = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                ram[addressTo+offset] = ram[addressFrom+offset]; //Set value at pointer to value at other address
                break;
            }

            case (5): {
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                int pointerAddress = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                i++;
                char constant = (signed char) (unsigned char) bytecode[i];
                lo = (unsigned char) ram[pointerAddress];
                hi = (unsigned char) ram[pointerAddress+1];
                int addressTo = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                i++;
                lo = (unsigned char) bytecode[i];
                i++;
                hi = (unsigned char) bytecode[i];
                int offset = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                ram[addressTo+offset] = constant; //Set value at pointer constant byte
                break;
            }


            case (4): {
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                int pointerAddress = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                i++;
                lo = (unsigned char) bytecode[i];
                i++;
                hi = (unsigned char) bytecode[i];
                int addressFrom = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                lo = (unsigned char) ram[pointerAddress];
                hi = (unsigned char) ram[pointerAddress+1];
                int addressTo = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                i++;
                lo = (unsigned char) bytecode[i];
                i++;
                hi = (unsigned char) bytecode[i];
                int offset = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                ram[addressFrom+offset] = ram[addressTo+offset]; //Get the value at pointer and set value at other address
                break;
            }

            case (42): {
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                opstack_head++;
                opstack[opstack_head] = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                break;
            }

            case (45): {
                short pop = opstack[opstack_head];
                opstack_head--;
                putchar(pop);
                break;
            }

            case (46): {
                short character = (short) getchar();
                opstack_head++;
                opstack[opstack_head] = character;
                break;
            }

            case (43): { //Pop8Bit
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                short pop = opstack[opstack_head];
                opstack_head--;
                ram[(short) (((hi & 0xFF) << 8) | (lo & 0xFF))] = (char) pop;
                break;
            }

            case (44): { //Pop16Bit
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                short address = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                short pop = opstack[opstack_head];
                opstack_head--;
                char lower = (char) (pop & 0xFF);
                char upper = (char) ((pop >> 8) & 0xFF);
                ram[address] = lower;
                ram[address+1] = upper;
                break;
            }

            case (41): { //PushByteAs16
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                short address = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                opstack_head++;
                opstack[opstack_head] = (short) ram[address];
                break;
            }

            case (40): { //Push16Bit
                //Parse address from file
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                short address = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                //Parse short from ram
                lo = (unsigned char) ram[address];
                hi = (unsigned char) ram[address+1];
                opstack_head++;
                opstack[opstack_head] = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                break;
            }

            case (10): {
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = a + b;
                break;
            }

            case (11): {
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = b - a;
                break;
            }

            case (12): {
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = a * b;
                break;
            }

            case (13): {
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = b / a;
                break;
            }

            case (14): {
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = b % a;
                break;
            }

            case (15): { //Shift left
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = b << a;
                break;
            }

            case (16): { //Shift right
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = b >> a;
                break;
            }

            case (23): { //Xor
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = b ^ a;
                break;
            }

            case (20): { //Bool Not
                short a = opstack[opstack_head];
                opstack[opstack_head] = (short) (a == 1 ? 0 : 1);
                break;
            }

            case (22): { //Bool Or
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = (short) ((b==1 || a==1 ? 1 : 0));
                break;
            }

            case (24): { //Bool And
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = (short) ((b==1 && a==1 ? 1 : 0));
                break;
            }

            case (17): { //Greater than
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = (short) ((b > a ? 1 : 0));
                break;
            }

            case (18): { //Equals
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = (short) ((b == a ? 1 : 0));
                break;
            }

            case (25): { //Not equals
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = (short) ((b != a ? 1 : 0));
                break;
            }

            case (19): { //Lesser than
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = (short) ((b < a ? 1 : 0));
                break;
            }

            case (27): { //Lesser-equals
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = (short) ((b <= a ? 1 : 0));
                break;
            }

            case (26): { //Greater-equals
                short a = opstack[opstack_head];
                opstack_head--;
                short b = opstack[opstack_head];
                opstack[opstack_head] = (short) ((b >= a ? 1 : 0));
                break;
            }

            case (1): {
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                short addr = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                i++;
                char a = (signed char) (unsigned char) bytecode[i];
                ram[addr] = a;
                break;
            }

            case (3): {
                i++;
                short lo = (unsigned char) bytecode[i];
                i++;
                short hi = (unsigned char) bytecode[i];
                short addr = (short) (((hi & 0xFF) << 8) | (lo & 0xFF));
                i++;
                lo = (unsigned char) bytecode[i];
                i++;
                hi = (unsigned char) bytecode[i];
                ram[addr] = (char) lo;
                ram[addr+1] = (char) hi;
                break;
            }

            case (30): {
                i++;
                short pop = opstack[opstack_head];
                opstack_head--;
                if (pop == (short)1){
                    signed char a = (signed char) (unsigned char) bytecode[i];
                    i += a-1;
                }
                break;
            }

            case (31): {
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int m1 = (unsigned char) bytecode[i];
                i++;
                int m2 = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                short pop = opstack[opstack_head];
                opstack_head--;
                if (pop == (short)1){
                    i = (((hi & 0xFF) << 24) | ((m2 & 0xFF) << 16) | ((m1 & 0xFF) << 8) | (lo & 0xFF))-1;
                }
                break;
            }

            case (32): {
                i++;
                int lo = (unsigned char) bytecode[i];
                i++;
                int m1 = (unsigned char) bytecode[i];
                i++;
                int m2 = (unsigned char) bytecode[i];
                i++;
                int hi = (unsigned char) bytecode[i];
                short pop = opstack[opstack_head];
                opstack_head--;
                if (pop != (short)1){
                    i = (((hi & 0xFF) << 24) | ((m2 & 0xFF) << 16) | ((m1 & 0xFF) << 8) | (lo & 0xFF))-1;
                }
                break;
            }

            default: {
                printf("%s\nFatal Error: Unknown instruction %d", ANSI_RED, (unsigned char) bytecode[i]);
                exit(1);
            }
        }
    }
    jFatal("Program did not call exit 0, no known success!");
}