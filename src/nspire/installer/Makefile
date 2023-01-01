TARGET=angband-installer
CROSS=arm-none-eabi
GCC=nspire-gcc

default: all

.PHONY: all clean default send

#FIXME: zip uses relative path ../lib instead of lib/
LIBFILES = $(shell find $(addprefix ../../../lib/, gamedata customize help screens) ! -name Makefile ! -name .deps ! -name font*.prf)

angband.zip: ../../angband.tns ../pdcfont.bmp.tns
	$(eval ZIPDIR=$(PWD))
	$(eval TMPDIR=$(shell mktemp -d))
	mkdir -p $(TMPDIR)/lib
	cp -r $(LIBFILES) $(TMPDIR)/lib
	cp -r $^ $(TMPDIR)
	cd $(TMPDIR) && zip -r $(ZIPDIR)/angband.zip ./*
	rm -r $(TMPDIR)

../../angband.tns: ../../angband
	cd .. && genzehn --input ../angband --output ../angband.tns

../../angband: ../../angband.o
	cd .. && $(MAKE) -f Makefile.nsp -j4

zip.h:

$(TARGET).elf:  main.c zip.c zip.h miniz.h
	$(GCC) main.c zip.c -Os -o $@

$(TARGET).tns: $(TARGET).elf angband.zip
	genzehn --input $< --output $@
	echo -n FUPA >> $@ # magic number (F.U.P.A)
	cat angband.zip >> $@

all: $(TARGET).tns angband.zip

send-prog: ../../angband.tns
	./firebird-send ../../angband.tns

send: all
	./firebird-send $(TARGET).tns

clean:
	rm -rf $(TARGET).elf $(TARGET).tns angband.zip angband
