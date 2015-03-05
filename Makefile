# Makefile
# Makefile do Projeto AssemblerM.

# DEFINIÇÕES DE ARQUIVOS #####################
# Arquivos de código-fonte
IMAIN_SRC		= src/imain.c
ASSEMBLER_SRC	= src/assembler.c
ASMLOADER_SRC	= src/asmLoader.c
ASMWRITER_SRC	= src/asmWriter.c

# Arquivos-objeto
IMAIN_OBJ		= obj/imain.o
ASSEMBLER_OBJ	= obj/assembler.o
ASMLOADER_OBJ	= obj/asmLoader.o
ASMWRITER_OBJ	= obj/asmWriter.o

# Arquivos-cabeçalho
ASSEMBLER_H		= inc/assembler.h
ASMLOADER_H		= inc/asmLoader.h
ASMWRITER_H		= inc/asmWriter.h

# Símbolos de arquivos de saída
OUTPUT_NAME_EXEC		= AssemblerM
OUTPUT_FULLPATH_EXEC	= bin/$(OUTPUT_NAME_EXEC)
LN_SYMBOL				= $(OUTPUT_NAME_EXEC)


# DEFINIÇÕES PARA COMPILAÇÃO #################
COMPILER 		= gcc
CFLAG 			= -c
LFLAG 			= -o
#LIBFLAG 		=
SRC 			= $(IMAIN_SRC) $(ASSEMBLER_SRC) $(ASMLOADER_SRC) $(ASMWRITER_SRC)

OBJ				= $(IMAIN_OBJ) $(ASSEMBLER_OBJ) $(ASMLOADER_OBJ) $(ASMWRITER_OBJ)

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

$(BIN): $(OBJ)
	$(COMPILER) $(LFLAG) $(BIN) $(OBJ) $(LIBFLAG)


# GERAÇÃO DO LINK SIMBÓLICO #################
LN_SYMBOL:
	rm -f $(OUTPUT_NAME_EXEC)
	ln -s $(OUTPUT_FULLPATH_EXEC)
	
# CRIAÇÃO DE PASTAS
mk_dir:
	mkdir -p bin data obj

clean:
	rm -f $(OUTPUT_FULLPATH_EXEC) $(LN_SYMBOL) data/* *~ *.swp *.swo \
	$(OBJ)

