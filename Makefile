TARGET = todo
CC = gcc

PREF_SRC_LIB = ./src/lib/
PREF_SRC_PROG = ./src/todo/
PREF_OBJ = ./obj/

all: $(TARGET)

$(TARGET): $(PREF_OBJ)todo.o $(PREF_OBJ)todo_list.o
	$(CC) -Wall -o $@.exe $(PREF_OBJ)todo.o $(PREF_OBJ)todo_list.o

$(PREF_OBJ)todo.o: src/todo/todo.c
	$(CC) -c $(PREF_SRC_PROG)todo.c -o $@

$(PREF_OBJ)todo_list.o: src/lib/todo_list.c
	$(CC) -c $(PREF_SRC_LIB)todo_list.c -o $@

run:
	./$(TARGET).exe

clean:
	rm $(TARGET).exe $(PREF_OBJ)*.o