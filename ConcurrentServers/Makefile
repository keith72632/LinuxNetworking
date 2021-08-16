CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
FLAGS = -g

all: ${OBJS}
	${CC} $^ -o main

%.o: %.c
	${CC} ${FLAGS} -c $^ -o $@

clean:
	rm *.o main
