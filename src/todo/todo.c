#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/todo_list.h"

int main()
{
    todo_list *list = malloc(sizeof(*list));
    list->todo = (char **)malloc(sizeof(char *));
    list->size = -1;
    list->selection = (int *)calloc(1, sizeof(int));
    list->color = (int *)calloc(1, sizeof(int));
    FILE *file = fopen("../todo-лист.txt", "r");
    char *g = malloc(sizeof(char) * 1000);
    if (file != NULL)
        fgets(g, 1000, file);
    else
    {
        free(g);
        g = NULL;
    }
    int count;
    if (g != NULL && strlen(g) != 0)
        count = atoi(g);
    else
        count = 0;
    while (1)
    {
        printf("\e[1;1H\e[2J");
        menu();
        char *_code = malloc(sizeof(char) * 10);
        if (count <= 0)
            fgets(_code, 10, stdin);
        else
            fgets(_code, 10, file);
        int code = atoi(_code);
        free(_code);
        printf("\e[1;1H\e[2J");
        if (code == 1 || code == 2 || code == 3 || code == 4 || code == 5)
        {
            if (code == 5)
            {
                break;
            }
            if (code == 1)
            {
                char *todo = malloc(sizeof(char) * 101);
                int n = 1;
                while (n != 0)
                {
                    printf("Введите задачу (не более 100 символов):\n");
                    if (count <= 0)
                        fgets(todo, 101, stdin);
                    else
                        fgets(todo, 101, file);
                    if (todo != NULL)
                        n = add_todo(list, todo);
                    else
                        printf("Задача не введена. ");
                    printf("\e[1;1H\e[2J");
                }
            }
            if (code == 2)
            {
                int n = -1, num1;
                char *num = malloc(sizeof(char) * 10);
                while (n != 0)
                {
                    printf("Введите номер задачи: ");
                    if (count <= 0)
                        fgets(num, 10, stdin);
                    else
                        fgets(num, 10, file);
                    if (num != NULL)
                        num1 = atoi(num);
                    n = delete_todo(list, num1);
                    printf("\e[1;1H\e[2J");
                }
                free(num);
            }
            if (code == 3)
            {
                print_todo_list(list);
                if (count <= 0)
                    getc(stdin);
                else
                    getc(file);
                printf("\e[1;1H\e[2J");
            }
            if (code == 4)
            {
                while (1)
                {
                    printf("[1] - Подчёркивание\n");
                    printf("[2] - Цвет\n");
                    printf("[3] - Вернуться в меню\n");
                    int code1, l = -1;
                    char *_code1 = malloc(sizeof(char) * 10);
                    if (count <= 0)
                        fgets(_code1, 10, stdin);
                    else
                        fgets(_code1, 10, file);
                    code1 = atoi(_code1);
                    free(_code1);
                    printf("\e[1;1H\e[2J");
                    if (code1 == 1 || code1 == 2 || code1 == 3)
                    {
                        if (code1 == 3)
                        {
                            printf("\e[1;1H\e[2J");
                            break;
                        }
                        if (code1 == 2)
                        {
                            int n = -1;
                            char *code2 = malloc(sizeof(char) * 10);
                            while (n < 0 || n > 14)
                            {
                                printf("Пример:\n\n");
                                print_color();
                                printf("\nВведите код цвета: ");
                                if (count <= 0)
                                    fgets(code2, 10, stdin);
                                else
                                    fgets(code2, 10, file);
                                if (code2 != NULL)
                                    n = atoi(code2);
                                printf("\e[1;1H\e[2J");
                                if (n < 0 || n > 14)
                                    printf("Не верный код цвета. ");
                            }
                            free(code2);
                            l = n;
                        }
                        if (code1 == 1)
                        {
                            int n = -1;
                            char *code2 = malloc(sizeof(char) * 10);
                            while (n < 0 || n > 1)
                            {
                                printf("Пример:\n\n");
                                print_selection();
                                printf("\nВведите код подчёркивания: ");
                                if (count <= 0)
                                    fgets(code2, 10, stdin);
                                else
                                    fgets(code2, 10, file);
                                if (code2 != NULL)
                                    n = atoi(code2);
                                printf("\e[1;1H\e[2J");
                                if (n < 0 || n > 1)
                                    printf("Не верный код подчёркивания. ");
                            }
                            free(code2);
                            l = n;
                        }
                    }
                    if (l != -1)
                    {
                        while (l != -1)
                        {
                            printf("Введите номер строки к которой хотите применить форматирование вывода: ");
                            char *num = malloc(sizeof(char) * 10);
                            if (count <= 0)
                                fgets(num, 10, stdin);
                            else
                                fgets(num, 10, file);
                            if (num != NULL)
                            {
                                int n = atoi(num);
                                if (n > 0 && n <= list->size)
                                {
                                    if (code1 == 1)
                                        insert_selection(list, n, l);
                                    if (code1 == 2)
                                    {
                                        insert_color(list, n, l - 1);
                                        if (count > 0)
                                            count--;
                                    }
                                    break;
                                }
                            }
                            printf("\e[1;1H\e[2J");
                            printf("Недопустимый номер задачи.\n");
                        }
                        break;
                    }
                }
            }
        }
    }
    fclose(file);
    file = fopen("todo-лист.txt", "w");
    char *num = malloc(sizeof(char) * 10);
    sprintf(num, "%d", list->size);
    fputs(num, file);
    fprintf(file, "\n");
    for (int i = 0; i < list->size; i++)
    {
        fprintf(file, "1");
        fprintf(file, "\n");
        fprintf(file, "%s", list->todo[i]);
        fprintf(file, "4");
        fprintf(file, "\n");
        fprintf(file, "1");
        fprintf(file, "\n");
        sprintf(num, "%d", list->selection[i]);
        fprintf(file, "%s", num);
        fprintf(file, "\n");
        sprintf(num, "%d", i + 1);
        fprintf(file, "%s", num);
        fprintf(file, "\n");
        fprintf(file, "4");
        fprintf(file, "\n");
        fprintf(file, "2");
        fprintf(file, "\n");
        sprintf(num, "%d", list->color[i] + 1);
        fprintf(file, "%s", num);
        fprintf(file, "\n");
        sprintf(num, "%d", i + 1);
        fprintf(file, "%s", num);
        fprintf(file, "\n");
    }
    fclose(file);
    free_todo_list(list);
}
