# Makefile for attoC

CC=gcc
CFLAGS= -Wall -g

VPATH += ./src
INCS=-I../inc

SRCS = $(wildcard ./src/*.c)
OBJS = $(SRCS:.c=.o)

.SUFFIXES: .c .o .h

MAIN = attoC

all: $(MAIN)
	@echo attoC has been successfully compiled.

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $@ $(OBJS)

.c.o: 
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) *.o ./$(MAIN) ./src/*.o


