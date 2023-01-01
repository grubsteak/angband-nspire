ANGBAND_FOLDER=/documents/lib
autoreconf -fi;
CFLAGS='-DPRIVATE_USER_PATH=\"/documents/lib/dumps/\"' \
 configdir=$(ANGBAND_FOLDER) \
 libdatadir=$(ANGBAND_FOLDER) \
 vardatadir=$(ANGBAND_FOLDER) \
 CC=nspire-gcc \
    ./configure --host=arm-none-eabi --with-no-install;

cd src; make -f Makefile.nsp -j8