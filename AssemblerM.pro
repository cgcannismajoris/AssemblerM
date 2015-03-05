TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/assembler.c \
    src/imain.c \
    src/asmLoader.c \
    src/asmWriter.c

HEADERS += \
    inc/assembler.h \
    inc/asmLoader.h \
    inc/asmWriter.h

OTHER_FILES += \
    Makefile
