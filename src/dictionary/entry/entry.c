/* entry.c
 * Implementaçao do TAD ENTRY.
 */

#include "entry.h"

ENTRY *entry_new(char *rotulo, int opcode)
{
	
	ENTRY *new = NULL;
	char *new_rot = NULL;

	if(rotulo != NULL && strlen(rotulo) <= 10){

		new = (ENTRY*)malloc(sizeof(ENTRY));
		new_rot = (char*)malloc(ENTRY_ROT_MAXLENGTH);

		if(new != NULL) 
		{
			if(new_rot != NULL)
			{
				new->rotulo = new_rot;	
				strncpy(new->rotulo, rotulo, ENTRY_ROT_MAXLENGTH);
				new->opcode = opcode;
			}
			else
			{ //new foi alocado mas o rótulo não
				free(new);
				new = ENTRY_EALLOC;
			}
		}
	}

    return new;
}

void entry_free(ENTRY *entry)
{

	free(entry->rotulo);
	free(entry);	

}

const char *entry_getRotulo(ENTRY *entry)
{
	if(entry != NULL)
	{
		return(entry->rotulo);
	}

	return(NULL);
}

uint8_t entry_getOpcode(ENTRY *entry)
{
	if(entry != NULL)
	{
		return(entry->opcode);
	}

	return(0);
}
