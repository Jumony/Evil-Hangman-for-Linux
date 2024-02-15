CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o my_string.o

all: string_driver unit_test

unit_test: unit_test.o my_string.o test_def.o
	$(CC) $(CFLAGS) unit_test.o my_string.o test_def.o -o unit_test

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o string_driver

unit_test.o: unit_test.c my_string.h unit_test.h
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o

test_def.o: test_def.c my_string.h unit_test.h
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o

main.o: main.c my_string.h
	$(CC) $(CFLAGS) -c main.c -o main.o

my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o

clean:
	rm string_driver
	rm $(OBJECTS)
