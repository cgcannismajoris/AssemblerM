/* reg.h
 * Implementação do TAD REG.
 */
#include "reg.h"

REG *reg_new(const char *name, uint8_t num)
{
    REG *novo;
    int c;

    if ((novo = (REG *)malloc(sizeof(REG))) == NULL)
        return REG_EALLOC;

    c = strlen(name);

    if ((novo->regName = (char *)malloc(c)) == NULL)
        return REG_EALLOC;

    strcpy(novo->regName, name);
    novo->regNum = num;

    return novo;
}

void reg_free(REG *reg)
{
    free(reg->regName);
    free(reg);
}

char *reg_getName(REG *reg)
{
    return reg->regName;
}

uint8_t reg_getNum(REG *reg)
{
    return reg->regNum;
}
