/* reg.h
 * Implementação do TAD REG.
 */
#include "reg.h"

REG *reg_new(const char *name)
{
    REG *novo;
    int c;

    if ((novo = (REG *)malloc(sizeof(REG))) == NULL)
        return REG_EALLOC;

    c = strlen(name);

    if ((novo->name = (char *)malloc(c)) == NULL)
        return REG_EALLOC;

    strcpy(novo->name, name);

    return novo;
}

void reg_free(REG *reg)
{
	free(reg->name);
    free(reg);
}

char *reg_getName(REG *reg)
{
    return reg->name;
}

