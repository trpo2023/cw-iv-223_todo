#include "todo_list.h"

#define CSI "\x1B\x5B"

char colors[][5] = {"0;30", /* Black */ "1;30",  /* Dark Gray */
                    "0;31", /* Red */ "1;31",    /* Bold Red */
                    "0;32", /* Green */ "1;32",  /* Bold Green */
                    "0;33", /* Yellow */ "1;33", /* Bold Yellow */
                    "0;34", /* Blue */ "1;34",   /* Bold Blue */
                    "0;35", /* Purple */ "1;35", /* Bold Purple */
                    "0;36", /* Cyan */ "1;36" /*Bold Cyan */};

int add_todo(todo_list *list, char *todo)
{
    if (list == NULL)
        return -1;
    if (todo == NULL || strlen(todo) == 0)
    {
        printf("Задача не введена. ");
        return 1;
    }
    if (list->size == -1)
        list->size++;
    list->size++;
    list->todo = realloc(list->todo, sizeof(char *) * list->size);
    list->selection = realloc(list->selection, sizeof(int) * list->size);
    list->color = realloc(list->color, sizeof(int) * list->size);
    list->todo[list->size - 1] = todo;
    return 0;
}

int delete_todo(todo_list *list, int number_todo)
{
    if (list == NULL)
        return -1;
    if (number_todo > list->size || number_todo < 1)
    {
        printf("Недопустимый номер задачи. ");
        return 1;
    }
    while (number_todo < list->size)
    {
        list->todo[number_todo - 1] = list->todo[number_todo];
        list->selection[number_todo - 1] = list->selection[number_todo];
        list->color[number_todo - 1] = list->color[number_todo];
        number_todo++;
    }
    list->size--;
    list->todo = realloc(list->todo, sizeof(char *) * list->size);
    list->selection = realloc(list->selection, sizeof(int) * list->size);
    list->color = realloc(list->color, sizeof(int) * list->size);
    return 0;
}
