autoreconf -fi; CC=nspire-gcc ./configure --host=arm-none-eabi
make -j8;
cd src/nspire/installer; make