ANGBAND_FOLDER=/documents/lib
autoreconf -fi;

CFLAGS='-DPRIVATE_USER_PATH=\"/documents/lib/dumps/\"' \
 CC=nspire-gcc \
    ./configure --host=arm-none-eabi --with-nspire-install;
