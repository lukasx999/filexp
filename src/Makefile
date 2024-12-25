CC=gcc
CFLAGS=-Wall -Wextra -ggdb -std=c99 -pedantic
LIBS=-lraylib
DEPS=explorer.h ui.h

all: main.o explorer.o ui.o $(DEPS)
	@$(CC) $(CFLAGS) $(LIBS) $^ -o out
	@echo CC $^

%.o: %.c Makefile $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo CC $<

clean:
	rm *.o out

.PHONY: clean
