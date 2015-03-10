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
    char *      regName;
    uint8_t     regNum;
} REG;

REG *       reg_new(const char *name, uint8_t num);
void        reg_free(REG *reg);

char *      reg_getName(REG *reg);
uint8_t     reg_getNum(REG *reg);


#endif /* REG_HEADER */
