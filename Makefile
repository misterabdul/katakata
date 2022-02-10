CFLAGS = -std=c99 -Wall -Wextra -static -lm $(CFLAG)
CP ?= cp
PREFIX ?= /usr/local

SRCDIR = src
BINDIR = bin
OBJDIR = obj

.PHONY: all clean install uninstall

all: ${BINDIR}/katakata

clean:
	${RM} -rf ${OBJDIR}/*

install: ${BINDIR}/katakata
	${CP} ${BINDIR}/katakata ${PREFIX}/bin/

uninstall:
	${RM} ${PREFIX}/bin/katakata

${BINDIR}/katakata: ${OBJDIR}/katakata.o
	${CC} -o $@ $^ ${CFLAGS}

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} -o $@ -c $< ${CFLAGS}
