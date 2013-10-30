MKDIR=/bin/mkdir
RM=/bin/rm

EXEC=access

CC=/usr/bin/gcc
LD=/usr/bin/ld
CFLAGS=-g3 -Wall

all: build

build: clean
	${MKDIR} -p build
	${CC} ${CFLAGS} -c -I src -o build/params.o src/params.c
	${CC} ${CFLAGS} -c -I src -o build/access.o src/access.c
	${CC} ${CFLAGS} -I src -o ${EXEC} build/access.o build/params.o

install:
	ln -s `pwd`/${EXEC} /usr/local/bin/${EXEC}

clean:
	${RM} -rf bin
	${RM} -rf build
