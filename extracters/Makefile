# all of these can be over-ridden on the "make" command line if they don't suit your environment.

CFLAGS=-O2 -Wall -Wshadow -Wextra -pedantic -Woverflow -Wstrict-overflow
BIN=/usr/local/bin
INSTALL=install
CC=gcc

SUBDIRS=backup ckabstape cpytap dbtap mmdir mtdump ods2 rawcopy rawtap rstsflx sdsdump tpdump

.PHONY: all clean install uninstall

# Omitted: backup, ods2: need more complicated Makefiles.
all:
	for subdir in backup ckabstape cpytap dbtap mmdir mtdump rawcopy rawtap sdsdump tpdump; do \
		$(MAKE) -C $$subdir CFLAGS="$(CFLAGS)" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)"; \
	done
	$(MAKE) -C rstsflx CFLAGS="$(CFLAGS) -Wno-sign-compare -Wno-shadow -Wno-format-pedantic -Wno-unused-variable -Wno-unused-parameter -Wno-unused-function" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)"
	$(MAKE) -C ods2 CFLAGS="$(CFLAGS) -Wno-dollar-in-identifier-extension -Wno-unused-parameter -Wno-unused-but-set-variable -Wno-sign-compare -Wno-shadow -Wno-format-pedantic -Wno-strict-prototypes" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)"

clean install uninstall:
	for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir CFLAGS="$(CFLAGS)" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)" $@; \
	done
