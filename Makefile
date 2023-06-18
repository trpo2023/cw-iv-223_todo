TARGET = todo
CCFLAGS=-Wall -Wextra -Wconversion -Wredundant-decls -Wshadow -Wno-unused-parameter -O3
CC=clang

PREF_BIN = ./bin/
PREF_SRC_LIB = ./src/lib/
PREF_SRC_PROG = ./src/todo/
PREF_OBJ = ./obj/
PREF_OBJ_TESTS = ./obj/tests/
PREF_TESTS_TEST = ./tests/test/
PREF_TESTS_THIRDPARTY = ./tests/thirdparty/

all: $(PREF_BIN)$(TARGET)

$(PREF_BIN)$(TARGET): $(PREF_OBJ)todo.o $(PREF_OBJ)todo_list.o
	gcc -Wall -o $@.exe $(PREF_OBJ)todo.o $(PREF_OBJ)todo_list.o

$(PREF_OBJ)todo.o: src/todo/todo.c
	gcc -c $(PREF_SRC_PROG)todo.c -o $@

$(PREF_OBJ)todo_list.o: src/lib/todo_list.c
	gcc -c $(PREF_SRC_LIB)todo_list.c -o $@

run:
	$(PREF_BIN)$(TARGET).exe

clean:
	rm $(PREF_BIN)$(TARGET).exe $(PREF_OBJ)*.o $(PREF_BIN)test $(PREF_OBJ_TESTS)*.o

test: $(PREF_OBJ_TESTS)main.c.o $(PREF_TESTS_THIRDPARTY)ctest.h $(PREF_OBJ_TESTS)parser_test.c.o $(PREF_OBJ)todo_list.o
	$(CC) $(LDFLAGS) $(PREF_OBJ_TESTS)main.c.o $(PREF_OBJ_TESTS)parser_test.c.o $(PREF_OBJ)todo_list.o -o $(PREF_BIN)test

$(PREF_OBJ_TESTS)main.c.o: $(PREF_TESTS_TEST)main.c $(PREF_TESTS_THIRDPARTY)ctest.h
	$(CC) $(CCFLAGS) -c -o $@ $<

$(PREF_OBJ_TESTS)parser_test.c.o: $(PREF_TESTS_TEST)parser_test.c $(PREF_TESTS_THIRDPARTY)ctest.h
	$(CC) $(CCFLAGS) -c -o $@ $<

test_run:
	$(PREF_BIN)test

clean_test:
	rm -f $(PREF_BIN)test  $(PREF_OBJ_TESTS)*.o