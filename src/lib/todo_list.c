#include "todo_list.h"

#define CSI "\x1B\x5B"

char colors[][5]
        = {"0;30",
           /* Black */ "1;30", /* Dark Gray */
           "0;31",
           /* Red */ "1;31", /* Bold Red */
           "0;32",
           /* Green */ "1;32", /* Bold Green */
           "0;33",
           /* Yellow */ "1;33", /* Bold Yellow */
           "0;34",
           /* Blue */ "1;34", /* Bold Blue */
           "0;35",
           /* Purple */ "1;35", /* Bold Purple */
           "0;36",
           /* Cyan */ "1;36" /*Bold Cyan */};

int add_todo(todo_list* list, char* todo)
{
    if (list == NULL)
        return -1;
    if (todo == NULL || strlen(todo) == 0) {
        printf("Задача не введена. ");
        return 1;
    }
    if (list->size == -1)
        list->size++;
    list->size++;
    list->todo = realloc(list->todo, sizeof(char*) * list->size);
    list->selection = realloc(list->selection, sizeof(int) * list->size);
    list->color = realloc(list->color, sizeof(int) * list->size);
    list->todo[list->size - 1] = todo;
    return 0;
}

int delete_todo(todo_list* list, int number_todo)
{
    if (list == NULL)
        return -1;
    if (number_todo > list->size || number_todo < 1) {
        printf("Недопустимый номер задачи. ");
        return 1;
    }
    while (number_todo < list->size) {
        list->todo[number_todo - 1] = list->todo[number_todo];
        list->selection[number_todo - 1] = list->selection[number_todo];
        list->color[number_todo - 1] = list->color[number_todo];
        number_todo++;
    }
    list->size--;
    list->todo = realloc(list->todo, sizeof(char*) * list->size);
    list->selection = realloc(list->selection, sizeof(int) * list->size);
    list->color = realloc(list->color, sizeof(int) * list->size);
    return 0;
}

int print_todo_list(todo_list* list)
{
    if (list == NULL)
        return -1;
    printf("%s%sm                            Список задач %s0m \n\n",
           CSI,
           colors[7],
           CSI);
    if (list->size == 0 || list->size == -1) {
        printf("%s%sm Задач нет.. %s0m \n", CSI, colors[2], CSI);
        return 0;
    }
    for (int i = 0; i < list->size; i++) {
        if (list->selection[i] == 1) {
            if (list->color[i] == 0)
                printf("%s%smЗадача №%d: %s0m %s4m%s%s0m\n\n",
                       CSI,
                       colors[2],
                       i + 1,
                       CSI,
                       CSI,
                       list->todo[i],
                       CSI);
            else
                printf("%s%smЗадача №%d: %s0m %s4m%s%sm%s%s0m\n\n",
                       CSI,
                       colors[2],
                       i + 1,
                       CSI,
                       CSI,
                       CSI,
                       colors[list->color[i]],
                       list->todo[i],
                       CSI);
        } else {
            if (list->color[i] == 0)
                printf("%s%smЗадача №%d:%s0m  %s%s0m\n\n",
                       CSI,
                       colors[2],
                       i + 1,
                       CSI,
                       list->todo[i],
                       CSI);
            else
                printf("%s%smЗадача №%d:%s0m%s%sm  %s%s0m\n\n",
                       CSI,
                       colors[2],
                       i + 1,
                       CSI,
                       CSI,
                       colors[list->color[i]],
                       list->todo[i],
                       CSI);
        }
    }
    return 0;
}

void insert_selection(todo_list* list, int num_todo, int selection)
{
    list->selection[num_todo - 1] = selection;
}

void insert_color(todo_list* list, int num_todo, int color)
{
    list->color[num_todo - 1] = color;
}

void print_selection()
{
    printf("[0] - Без подчёркивания%s0m\n", CSI);
    printf("[1] - %s4mС подчёркиванием%s0m\n", CSI, CSI);
}

void print_color()
{
    printf("[0] - Белый\n");
    printf("[1] - %s%sm  Чёрный%s0m\n", CSI, colors[0], CSI);
    printf("[2] - %s%sm  Темно-серый%s0m\n", CSI, colors[1], CSI);
    printf("[3] - %s%sm  Красный%s0m\n", CSI, colors[2], CSI);
    printf("[4] - %s%sm  Ярко-красный%s0m\n", CSI, colors[3], CSI);
    printf("[5] - %s%sm  Зелёный%s0m\n", CSI, colors[4], CSI);
    printf("[6] - %s%sm  Ярко-зелёный%s0m\n", CSI, colors[5], CSI);
    printf("[7] - %s%sm  Жёлтый%s0m\n", CSI, colors[6], CSI);
    printf("[8] - %s%sm  Ярко-жёлтый%s0m\n", CSI, colors[7], CSI);
    printf("[9] - %s%sm  Синий%s0m\n", CSI, colors[8], CSI);
    printf("[10] - %s%sm  Ярко-синий%s0m\n", CSI, colors[9], CSI);
    printf("[11] - %s%sm  Фиолетовый%s0m\n", CSI, colors[10], CSI);
    printf("[12] - %s%sm  Ярко-фиолетовый%s0m\n", CSI, colors[11], CSI);
    printf("[13] - %s%sm  Голубой%s0m\n", CSI, colors[12], CSI);
    printf("[14] - %s%sm  Ярко-голубой%s0m\n", CSI, colors[13], CSI);
}

void menu()
{
    printf("\n\n[1] - Добавить задачу\n[2] - Удалить задачу\n[3] - Выыести "
           "список задач\n[4] - Изменить формат вывода задачи\n[5] - Завершить "
           "программу\n");
}

void free_todo_list(todo_list* list)
{
    if (list->size != -1)
        for (int i = 0; i < list->size; i++) {
            free(list->todo[i]);
        }
    free(list->color);
    free(list->selection);
    free(list->todo);
    free(list);
}
