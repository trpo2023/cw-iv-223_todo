#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** todo;
    int size;
    int* selection;
    int* color;
} todo_list;

int add_todo(todo_list* list, char* todo);

int delete_todo(todo_list* list, int number_todo);

int print_todo_list(todo_list* list);

void insert_selection(todo_list* list, int num_todo, int selection);

void insert_color(todo_list* list, int num_todo, int color);

void print_selection();

void print_color();

void menu();

void free_todo_list(todo_list* list);
