# Makefile
# Makefile do Projeto AssemblerM.

# DEFINIÇÕES DE ARQUIVOS #####################
# Arquivos de código-fonte
IMAIN_SRC		= src/imain.c
ASSEMBLER_SRC	= src/assembler/assembler.c
ASMLOADER_SRC	= src/asmLoader/asmLoader.c
ASMWRITER_SRC	= src/asmWriter/asmWriter.c
INSTRUCTION_SRC	= src/instruction/instruction.c
DICTIONARY_SRC	= src/dictionary/dictionary.c
ENTRY_SRC		= src/dictionary/entry/entry.c
DICWRITER_SRC	= src/dictionary/dicWriter/dicWriter.c
DICLOADER_SRC	= src/dictionary/dicLoader/dicLoader.c


# Arquivos-cabeçalho
ASSEMBLER_H		= src/assembler/assembler.h
ASMLOADER_H		= src/asmLoader/asmLoader.h
ASMWRITER_H		= src/asmWriter/asmWriter.h
INSTRUCTION_H	= src/instruction/instruction.h
DICTIONARY_H	= src/dictionary/dictionary.h
ENTRY_H			= src/dictionary/entry/entry.h
DICWRITER_H		= src/dictionary/dicWriter/dicWriter.h
DICLOADER_H		= src/dictionary/dicLoader/dicLoader.h


# Arquivos-objeto
IMAIN_OBJ		= obj/imain.o
ASSEMBLER_OBJ	= obj/assembler.o
ASMLOADER_OBJ	= obj/asmLoader.o
ASMWRITER_OBJ	= obj/asmWriter.o
INSTRUCTION_OBJ	= obj/instruction.o
DICTIONARY_OBJ	= obj/dictionary.o
ENTRY_OBJ		= obj/entry.o
DICWRITER_OBJ	= obj/dicWriter.o
DICLOADER_OBJ	= obj/dicLoader.o


# Símbolos de arquivos de saída
OUTPUT_NAME_EXEC		= AssemblerM
OUTPUT_FULLPATH_EXEC	= bin/$(OUTPUT_NAME_EXEC)
LN_SYMBOL				= $(OUTPUT_NAME_EXEC)


# DEFINIÇÕES PARA COMPILAÇÃO #################
COMPILER 		= gcc
CFLAG 			= -c
LFLAG 			= -o
#LIBFLAG 		=
SRC 			= $(IMAIN_SRC) $(ASSEMBLER_SRC) $(ASMLOADER_SRC) \
$(ASMWRITER_SRC) $(INSTRUCTION_SRC) $(DICTIONARY_SRC) $(ENTRY_SRC) \
$(DICWRITER_SRC) $(DICLOADER_SRC)

OBJ				= $(IMAIN_OBJ) $(ASSEMBLER_OBJ) $(ASMLOADER_OBJ) \
$(ASMWRITER_OBJ) $(INSTRUCTION_OBJ) $(DICTIONARY_OBJ) $(ENTRY_OBJ) \
$(DICWRITER_OBJ) $(DICLOADER_OBJ)

BIN				= $(OUTPUT_FULLPATH_EXEC)


all: mk_dir $(BIN)

$(IMAIN_OBJ): $(IMAIN_SRC)
	$(COMPILER) $(CFLAG) $(IMAIN_SRC) $(LFLAG) $(IMAIN_OBJ)

$(ASSEMBLER_OBJ): $(ASSEMBLER_H) $(ASSEMBLER_SRC)
	$(COMPILER) $(CFLAG) $(ASSEMBLER_SRC) $(LFLAG) $(ASSEMBLER_OBJ)

$(ASMLOADER_OBJ): $(ASMLOADER_H) $(ASMLOADER_SRC)
	$(COMPILER) $(CFLAG) $(ASMLOADER_SRC) $(LFLAG) $(ASMLOADER_OBJ)

$(ASMWRITER_OBJ): $(ASMWRITER_H) $(ASMWRITER_SRC)
	$(COMPILER) $(CFLAG) $(ASMWRITER_SRC) $(LFLAG) $(ASMWRITER_OBJ)

$(INSTRUCTION_OBJ): $(INSTRUCTION_H) $(INSTRUCTION_SRC)
	$(COMPILER) $(CFLAG) $(INSTRUCTION_SRC) $(LFLAG) $(INSTRUCTION_OBJ)

$(DICTIONARY_OBJ): $(DICTIONARY_H) $(DICTIONARY_SRC)
	$(COMPILER) $(CFLAG) $(DICTIONARY_SRC) $(LFLAG) $(DICTIONARY_OBJ)

$(ENTRY_OBJ): $(ENTRY_H) $(ENTRY_SRC)
	$(COMPILER) $(CFLAG) $(ENTRY_SRC) $(LFLAG) $(ENTRY_OBJ)

$(DICWRITER_OBJ): $(DICWRITER_H) $(DICWRITER_SRC)
	$(COMPILER) $(CFLAG) $(DICWRITER_SRC) $(LFLAG) $(DICWRITER_OBJ)

$(DICLOADER_OBJ): $(DICLOADER_H) $(DICLOADER_SRC)
	$(COMPILER) $(CFLAG) $(DICLOADER_SRC) $(LFLAG) $(DICLOADER_OBJ)

$(BIN): $(OBJ)
	$(COMPILER) $(LFLAG) $(BIN) $(OBJ) $(LIBFLAG)


# GERAÇÃO DO LINK SIMBÓLICO #################
LN_SYMBOL:
	rm -f $(OUTPUT_NAME_EXEC)
	ln -s $(OUTPUT_FULLPATH_EXEC)
	
# CRIAÇÃO DE PASTAS #########################
mk_dir:
	mkdir -p bin data obj

clean:
	rm -f $(OUTPUT_FULLPATH_EXEC) $(LN_SYMBOL) *~ *.swp *.swo \
	$(OBJ)

