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
    uint32_t        labelLineNumber;
    struct _label * next;
} LABEL;

LABEL *     label_new(const char *name, uint32_t number);
void        label_free(LABEL *label);

char *      label_getName(LABEL *label);
uint32_t    label_getLine(LABEL *label);

#endif /* LABEL_HEADER */
