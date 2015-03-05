TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	src/assembler/assembler.c \
    src/imain.c \
	src/asmLoader/asmLoader.c \
	src/asmWriter/asmWriter.c

HEADERS += \
	src/assembler/assembler.h \
	src/asmLoader/asmLoader.h \
	src/asmWriter/asmWriter.h

OTHER_FILES += \
    Makefile
