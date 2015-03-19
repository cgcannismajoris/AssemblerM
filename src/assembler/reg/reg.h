/* reg.h
 * TAD REG.
 */
#ifndef REG_HEADER
#define REG_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define REG_EALLOC          NULL
#define REG_EALLOC_MSG      "Falha ao alocar memória para REG."

typedef struct _reg
{
    char *      name;
} REG;

REG *       reg_new(const char *name);
void        reg_free(REG *reg);

char *      reg_getName(REG *reg);

#endif /* REG_HEADER */
