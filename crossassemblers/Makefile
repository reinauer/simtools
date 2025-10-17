# all of these can be over-ridden on the "make" command line if they don't suit your environment.

CFLAGS=-O2 -Wall -Wshadow -Wextra -pedantic -Woverflow -Wstrict-overflow
BIN=/usr/local/bin
INSTALL=install
CC=gcc

SUBDIRS=hpasm macro1 macro11 macro7 macro8x

.PHONY: all clean install uninstall

# Omitted: macro11: needs more complicated Makefiles.
all:
	$(MAKE) -C hpasm CFLAGS="$(CFLAGS) -Wno-missing-prototypes -Wno-deprecated-non-prototype -Wno-implicit-int -Wno-return-type -Wno-strict-prototypes" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)"
	$(MAKE) -C macro1 CFLAGS="$(CFLAGS) -Wno-missing-field-initializers -Wno-strict-prototypes -Wno-sign-compare -Wno-comment -Wno-shadow -Wno-logical-op-parentheses" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)"
	$(MAKE) -C macro7 CFLAGS="$(CFLAGS) -Wno-missing-field-initializers -Wno-strict-prototypes -Wno-sign-compare -Wno-parentheses -Wno-shadow -Wno-unused-parameter" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)"
	$(MAKE) -C macro8x CFLAGS="$(CFLAGS) -Wno-missing-field-initializers -Wno-strict-prototypes -Wno-sign-compare -Wno-parentheses -Wno-shadow" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)"
	$(MAKE) -C macro11 CFLAGS="$(CFLAGS) -Wno-unused-but-set-variable -Wno-strict-prototypes" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)"

clean install uninstall:
	for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir CFLAGS="$(CFLAGS)" BIN="$(BIN)" INSTALL="$(INSTALL)" CC="$(CC)" $@; \
	done
