all: main

main: todo.o todo_list.o
	gcc -Wall -o todo.exe todo.o todo_list.o

todo.o: src/todo/todo.c
	gcc -c todo.o src/todo/todo.c

todo_list.o: src/lib/todo_list.c
	gcc -c todo_list.o src/lib/todo_list.c

run:
	./todo.exe

clean:
	rm todo.exe
	rm todo.o
	rm todo_list.o