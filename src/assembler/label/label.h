/* label.h
 * TAD LABEL.
 */
#ifndef LABEL_HEADER
#define LABEL_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define LABEL_LABELNAMELENGTH   20


typedef struct _label
{
    char *          labelName[LABEL_LABELNAMELENGTH];
    uint64_t        labelLineNum;
    struct _label * next;
} LABEL;

LABEL *     label_new(const char *name, uint64_t num);
void        label_free(LABEL *label);

char *      label_getName(LABEL *label);
uint64_t    label_getLineNum(LABEL *label);

#endif /* LABEL_HEADER */
