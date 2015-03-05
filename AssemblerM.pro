TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/assembler.c \
    src/imain.c \
    src/asmLoader.c

HEADERS += \
    inc/assembler.h \
    inc/asmLoader.h

OTHER_FILES += \
    Makefile
