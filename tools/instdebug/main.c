#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../../src/instruction/instruction.h"

int main(int argc, char **argv)
{
    uint32_t numInst;
    TYPE_R tipo_r;
    TYPE_B tipo_b;
    TYPE_J tipo_j;


    FILE *file = fopen("data/first_mounted_file.out", "rb+");

    fread(&numInst, sizeof(uint32_t), 1, file);
    INSTRUCTION_SETINST(tipo_r, numInst);

    while (!feof(file))
    {

        if (tipo_r.opcode >= 1 && tipo_r.opcode <= 22)
        {
            INSTRUCTION_SETINST(tipo_r, numInst);

            printf("opcode: %d\n", tipo_r.opcode);
            printf("dest: %d\n", tipo_r.dest);
            printf("orig1: %d\n", tipo_r.orig1);
            printf("orig2: %d\n", tipo_r.orig2);
            printf("address: %d\n\n", tipo_r.address);
        }

        if (tipo_r.opcode >= 23 && tipo_r.opcode <= 44)
        {
            INSTRUCTION_SETINST(tipo_b, numInst);

            printf("opcode: %d\n", tipo_b.opcode);
            printf("reg1: %d\n", tipo_b.reg1);
            printf("reg2: %d\n", tipo_b.reg2);
            printf("address: %d\n\n", tipo_b.address);
        }

        if (tipo_r.opcode >= 45 && tipo_r.opcode <= 55)
        {
            INSTRUCTION_SETINST(tipo_j, numInst);

            printf("opcode: %d\n", tipo_j.opcode);
            printf("address: %d\n\n", tipo_j.address);
        }

        fread(&numInst, sizeof(uint32_t), 1, file);
        INSTRUCTION_SETINST(tipo_r, numInst);
    }

    fclose(file);

    return 0;
}
