/* reg.h
 * TAD REG.
 */
#ifndef REG_HEADER
#define REG_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct _reg
{
    char *      regName;
    u_int8_t    regNumber;
} REG;

REG *       reg_new(const char *name, uint8_t num);
void        reg_free(REG *reg);

char *      reg_getName(REG *reg);
u_int8_t    reg_getNum(REG *reg);


#endif /* REG_HEADER */
