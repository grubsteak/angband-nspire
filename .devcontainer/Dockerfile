# From root of angband-nspire
# DOCKER_BUILDKIT=1 docker build -t ndless --progress=plain -f src/nspire/Dockerfile . && docker run -ti ndless /bin/bash

FROM debian:bullseye

RUN set -eux; \
    apt-get update &&\
    apt-get install -y \
     build-essential git python3 python3-dev wget file libgmp-dev libmpfr-dev libmpc-dev zlib1g-dev \
     libbinutils libboost-program-options-dev texinfo gcc-arm-none-eabi php-dev zip

RUN useradd -m -d /home/ndless -p ndless ndless && chsh -s /bin/bash ndless
RUN git clone --recursive https://github.com/ndless-nspire/Ndless.git /home/ndless/Ndless
RUN chown -R ndless:ndless /home/ndless/Ndless &&\
    su ndless -c "cd /home/ndless/Ndless/ && git submodule init && git submodule update"
RUN cd /home/ndless/Ndless/ndless-sdk/toolchain &&\
    su ndless -c "./build_toolchain.sh && rm -rf download build-binutils build binutils-* gcc-* gdb-* newlib-* "
# DO NOT CHANGE ANYTHING ABOVE THIS LINE UNLESS YOU WANT TO WAIT FOR A VERY LONG TIME
RUN bash -c "echo -e 'PATH=\"\$PATH:/home/ndless/Ndless/ndless-sdk/bin:/home/ndless/PDCurses-nspire/nspire\"\nCC=nspire-gcc' | cat - /home/ndless/.bashrc" > /tmp/out; mv /tmp/out /home/ndless/.bashrc; 
RUN chown -R ndless:ndless /home/ndless/.bashrc
ENV BASH_ENV "/home/ndless/.bashrc"

RUN bash -c "echo \\#define PATH_MAX 256 >> /usr/lib/gcc/arm-none-eabi/*/*/limits.h;"

RUN su ndless -c "cd ~/Ndless/; find . -name '*' -exec sed -i -e 's/string_free/_string_free/g'  -e 's/has_colors/_has_colors/g' {} \\;  2>/dev/null; make -j8"
RUN su ndless -c "cd ~; git clone https://github.com/grubsteak/PDCurses-nspire.git; cd PDCurses-nspire/nspire; make -j8"

#RUN su ndless -c "cd ~/Ndless/; find . -name '*' -exec sed -i -e 's/string_free/_string_free/g'  -e 's/has_colors/_has_colors/g' {} \\;  2>/dev/null; \
                #   ln -s /home/ndless/angband-nspire/src/nspire/pdcurses/curses.h /home/ndless/angband-nspire/src/nspire/pdcurses/ncurses.h; \
                #   sed -i 's/#define USE_TPOSIX/\\/\\/#define USE_TPOSIX/g' /home/ndless/angband-nspire/src/main-gcu.c; \
                #   make -j8"

# start compiling angband here
# RUN echo CACHEBUST
RUN echo "#define st_mtime st_mtim.tv_sec" >> /home/ndless/Ndless/ndless-sdk/toolchain/install/arm-none-eabi/sys-include/sys/stat.h
