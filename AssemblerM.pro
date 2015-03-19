TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	src/assembler/assembler.c \
    src/imain.c \
	src/asmLoader/asmLoader.c \
	src/asmWriter/asmWriter.c \
    src/dictionary/dictionary.c \
    src/dictionary/entry/entry.c \
	src/dictionary/dicWriter/dicWriter.c \
	src/dictionary/dicLoader/dicLoader.c \
	src/instruction/instruction.c \
    src/assembler/label/label.c \
    src/assembler/reg/reg.c \
    src/scanner/tokens/tokens.c \
    src/scanner/scanner.c \
    tools/dicwriter/main.c \
    tools/instdebug/main.c

HEADERS += \
	src/assembler/assembler.h \
	src/asmLoader/asmLoader.h \
	src/asmWriter/asmWriter.h \
    src/dictionary/dictionary.h \
    src/dictionary/entry/entry.h \
	src/dictionary/dicWriter/dicWriter.h \
	src/dictionary/dicLoader/dicLoader.h \
	src/instruction/instruction.h \
    src/assembler/label/label.h \
    src/assembler/reg/reg.h \
    src/scanner/scanner.h \
    src/scanner/tokens/tokens.h

OTHER_FILES += \
    Makefile
