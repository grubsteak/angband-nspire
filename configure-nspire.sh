#!/bin/bash

autoreconf -fi;

# horrible C flags lol
CFLAGS='-DPRIVATE_USER_PATH=\"/documents/lib/dumps/\" -DDEFAULT_CONFIG_PATH=\"/documents/lib\" -DDEFAULT_LIB_PATH=\"/documents/lib\" -DDEFAULT_DATA_PATH=\"/documents/lib\"' \
    CC=nspire-gcc \
    ./configure --host=arm-none-eabi --with-no-install;