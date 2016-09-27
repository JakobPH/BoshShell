all: bosh

OBJS = redirect.o forback.o parser.o print.o bosh.o
LIBS= -lreadline -ltermcap
CC = gcc

bosh: ${OBJS}
	${CC} -o $@ ${OBJS} ${LIBS}

clean:
	rm -rf *o bosh
