#include "../thirdparty/ctest.h"
#include <string.h>

#include "../../src/lib/todo_list.h"

CTEST(add_todo_func, add__todo)
{
    char todo[50] = "Hallo!";
    todo_list* list = NULL;
    int n = add_todo(list, todo);
    ASSERT_EQUAL(-1, n);
    list = malloc(sizeof(*list));
    list->todo = (char**)malloc(sizeof(char*));
    list->size = -1;
    list->selection = (int*)calloc(1, sizeof(int));
    list->color = (int*)calloc(1, sizeof(int));
    n = add_todo(list, todo);
    ASSERT_EQUAL(0, n);
}

CTEST(add_todo_func, checking_the_added_line)
{
    todo_list* list = malloc(sizeof(*list));
    list->todo = (char**)malloc(sizeof(char*));
    list->size = -1;
    list->selection = (int*)calloc(1, sizeof(int));
    list->color = (int*)calloc(1, sizeof(int));
    char todo[50] = "Hallo!";
    add_todo(list, todo);
    ASSERT_STR(list->todo[0], "Hallo!");
}

CTEST(delete_todo_func, checking_line_deletion)
{
    todo_list* list = malloc(sizeof(*list));
    list->todo = (char**)malloc(sizeof(char*));
    list->size = -1;
    list->selection = (int*)calloc(1, sizeof(int));
    list->color = (int*)calloc(1, sizeof(int));
    char todo[50] = "Hallo!";
    add_todo(list, todo);
    ASSERT_EQUAL(1, list->size);
    delete_todo(list, 1);
    ASSERT_EQUAL(0, list->size);
}
CTEST(insert_selection_func, checking_the_underscore_change)
{
    todo_list* list = malloc(sizeof(*list));
    list->todo = (char**)malloc(sizeof(char*));
    list->size = -1;
    list->selection = (int*)calloc(1, sizeof(int));
    list->color = (int*)calloc(1, sizeof(int));
    char todo[50] = "Hallo!";
    add_todo(list, todo);
    insert_selection(list, 1, 1);
    ASSERT_EQUAL(1, list->selection[0]);
}

CTEST(insert_color_func, checking_for_color_changes)
{
    todo_list* list = malloc(sizeof(*list));
    list->todo = (char**)malloc(sizeof(char*));
    list->size = -1;
    list->selection = (int*)calloc(1, sizeof(int));
    list->color = (int*)calloc(1, sizeof(int));
    char todo[50] = "Hallo!";
    add_todo(list, todo);
    insert_color(list, 1, 2);
    ASSERT_EQUAL(2, list->color[0]);
}