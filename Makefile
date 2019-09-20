CC = gcc-9
PROGRAM = matrix
CFLAGS = -Wall -Wextra -Wpedantic -ggdb -std=gnu++17 -O0
LDLIBS =

default: bin/$(PROGRAM)

bin/$(PROGRAM): bin/$(PROGRAM).o
	$(CC) $^ $(LDLIBS) -o $@

bin/$(PROGRAM).o: src/$(PROGRAM).cc
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -fv bin/*.o bin/$(PROGRAM)
