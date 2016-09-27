all: bosh

OBJS = redirect.o forback.o parser.o print.o bosh.o
LIBS= -lreadline -ltermcap
CC = gcc

bosh: ${OBJS}
	${CC} -o $@ ${OBJS} ${LIBS}

pipe.o: pipe.h pipe.c
	gcc -o pi pipe.h pipe.c

clean:
	rm -rf *o bosh
