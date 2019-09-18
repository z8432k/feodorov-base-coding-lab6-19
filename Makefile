CC = gcc-9
PROGRAM = matrix
CFLAGS = -Wall -Wextra -Wpedantic -ggdb -std=gnu11 -O0
LDLIBS =

default: bin/$(PROGRAM)

bin/$(PROGRAM): bin/$(PROGRAM).o
	$(CC) $^ $(LDLIBS) -o $@

bin/$(PROGRAM).o: src/$(PROGRAM).c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -fv bin/*.o bin/$(PROGRAM)