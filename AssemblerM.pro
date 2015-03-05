TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/assembler.c \
    src/imain.c

HEADERS += \
    inc/assembler.h

OTHER_FILES += \
    Makefile
