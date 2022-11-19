TARGET=angband-installer
CROSS=arm-none-eabi
GCC=nspire-gcc
#GCC=gcc
default: all

.PHONY: all clean default send

#FIXME: zip uses relative path ../lib instead of lib/
LIBFILES = $(addprefix ../../../lib/, gamedata customize help screens user)
angband.zip: ../../angband.tns ../pdcfont.bmp.tns
	$(eval ZIPDIR=$(PWD))
	$(eval TMPDIR=$(shell mktemp -d))
	mkdir -p $(TMPDIR)/lib
	cp -r $(LIBFILES) $(TMPDIR)/lib
	cp -r $^ $(TMPDIR)
	cd $(TMPDIR) && zip -r $(ZIPDIR)/angband.zip ./*
	rm -r $(TMPDIR)

angband.zip.tns: angband.zip
	cp $< $@

../../angband.tns: ../../angband
	cd .. && genzehn --input ../angband --output ../angband.tns

../../angband: ../../angband.o
	cd .. && $(MAKE) -j4

zip.h:
$(TARGET).elf:  main.c zip.c zip.h miniz.h
	$(GCC) main.c zip.c -Os -o $@

$(TARGET).tns: $(TARGET).elf
	genzehn --input $< --output $@

all: $(TARGET).tns angband.zip.tns

send: all
	firebird-send $(TARGET).tns
	firebird-send angband.zip.tns

clean:
	rm -rf $(TARGET).elf $(TARGET).tns angband.zip angband.zip.tns angband
