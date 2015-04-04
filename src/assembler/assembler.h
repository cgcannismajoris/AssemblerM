/*
 * Nome do Arquivo:  assembler.h
 *       Descricao:  TAD responsável pela montagem do arquivo binário.
 *
 * Exported functions from assembler.c.
 * Copyright (C) 2015  Cristian Costa Mello and Gustavo Freitas de Amorim
 *
 * This is part of AssemblerM
 * AssemblerM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AssemblerM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#ifndef ASSEMBLER_HEADER
#define ASSEMBLER_HEADER

#include "assembler_struct.h"
#include "assemblerAnalyser.h"


ASSEMBLER * assembler_new();
void        assembler_free(ASSEMBLER *asmr);

int 		assembler_assemble(ASSEMBLER *asmr, 
							   const char *src, 
							   const char *bin,
							   const char *dicFile, 
							   int *inputValues, 
							   uint32_t length);

static int  __assembler_assemble_makeLabels(ASSEMBLER *asmr);

 
#endif /* ASSEMBLER_HEADER */
