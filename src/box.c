#include "box.h"
#include "unicode.h"
#include "colors.h"
#include "fruits.h"
#include "ball.h"
#include <unistd.h>

struct menu
{
    MENU father;
    char **items;
    int n_item;
    int h_border;
    int v_border;
    int selected;
    struct menu **sub_menus;
};

MENU innitMenu()
{
    MENU m = malloc(sizeof(struct menu));

    m->father = NULL;

    m->items = malloc(sizeof(char *));
    m->items[0] = NULL;

    m->n_item = 0;
    m->selected = 1;

    m->h_border = 0;
    m->v_border = 0;

    m->sub_menus = malloc(sizeof(struct menu *));
    m->sub_menus[0] = NULL;

    return m;
}

char *strcatrealloc_old(char *str1, char str2[])
{
    size_t str1len = 0;
    if (str1)
    {
        str1len = strlen(str1);
    }
    size_t str2len = strlen(str2);

    // It's easy to forget that strlen doesn't count the
    // trailing NULL character,
    size_t neededbufferlen = str1len + str2len + 1;

    char *strdest = (char *)malloc(neededbufferlen * sizeof(char));
    if (strdest)
    {
        if (str1)
        {
            strcpy(strdest, str1);
            strcat(strdest, str2);
        }
        else
        {
            strcpy(strdest, str2);
        }
    }

    if (str1)
        free(str1);

    return strdest;
}

char *strcatrealloc(char *str1, char str2[])
{
    if (!str2)
        return str1; // Se str2 for NULL, retorna str1 sem mudanças.

    size_t str1len = (str1) ? strlen(str1) : 0;
    size_t str2len = strlen(str2);

    // Realoca memória para str1, expandindo-a para acomodar str2 + '\0'
    char *new_str = realloc(str1, str1len + str2len + 1);
    if (!new_str)
    {
        return str1; // Se a realocação falhar, retorna a string original
    }

    // Copia ou concatena os dados na memória realocada
    strcpy(new_str + str1len, str2);

    return new_str;
}

char *addHead(size_t col, char *output)
{
    output = strcatrealloc(output, T_L_A);
    for (size_t i = 0; i < col; i++)
    {
        output = strcatrealloc(output, H_L);
    }
    output = strcatrealloc(output, T_R_A);
    output = strcatrealloc(output, "\n");
    return output;
}

char *addClose(size_t col, char *output)
{

    output = strcatrealloc(output, B_L_A);
    for (size_t i = 0; i < col; i++)
    {
        output = strcatrealloc(output, H_L);
    }
    output = strcatrealloc(output, B_R_A);
    output = strcatrealloc(output, "\n");
    output = strcatrealloc(output, RESET);
    return output;
}

char *addHBorder(size_t h_border, char *output)
{
    for (size_t i = 0; i < h_border; i++)
        output = strcatrealloc(output, " ");
    return output;
}

char *addEmptyLine(size_t col, char *output)
{
    output = strcatrealloc(output, V_L);
    for (size_t i = 0; i < col; i++)
        output = strcatrealloc(output, " ");
    output = strcatrealloc(output, V_L);
    output = strcatrealloc(output, "\n");
    return output;
}

char *addVBorder(size_t v_border, size_t col, char *output)
{
    for (size_t i = 0; i < v_border; i++)
        output = addEmptyLine(col, output);
    return output;
}

size_t strlen_unicode(char string[])
{
    if (!string)
        return 0; // string NULL return size 0

    size_t i, tmh = 0;
    for (i = 0; string[i] != '\0'; ++i)
    {

        // Support for unicode characters
        // in \xe2\x9c\x96 Style
        if (string[i] < 0)
        {
            if ((string[i + 1] < 0 && string[i + 2] < 0))
            {
                i = i + 2;
            }
        }

        // Support for Colors
        // in \033[00m Style
        if (string[i] == 27)
        {
            i = i + 4;
            tmh--;
        }

        tmh++;
    }
    return tmh;
}

char *addLine(char line[], char color[], size_t h_border, size_t maxArgsSize, char *output)
{
    output = strcatrealloc(output, V_L);
    output = addHBorder(h_border, output);
    output = strcatrealloc(output, color);
    output = strcatrealloc(output, line);
    output = strcatrealloc(output, RESET);
    size_t line_size = strlen_unicode(line);
    size_t buffer;
    if (maxArgsSize > line_size)
    {
        buffer = maxArgsSize - line_size + h_border;
    }
    else
    {
        buffer = h_border;
    }
    output = addHBorder(buffer, output);
    output = strcatrealloc(output, V_L);
    output = strcatrealloc(output, "\n");
    return output;
}

size_t maxArgsSize(char **args)
{
    int i = 0;
    size_t max = strlen_unicode(args[i++]);
    while (args[i])
    {
        size_t new_max = strlen_unicode(args[i]);
        if (new_max > max)
        {
            max = new_max;
        }
        i++;
    }
    return max;
}

char **processArgs(char text[])
{
    char *token;
    char *text_p = strdup(text);
    char *text_p_free = text_p;
    char **args = malloc(sizeof(char *) * 100);

    int num_args = 0;

    while ((token = strtok_r(text_p, "\n", &text_p)))
    {
        args[num_args] = strdup(token);
        num_args++;
    }
    args[num_args] = NULL;

    free(text_p_free);
    return args;
}

char *makeBox(char text[], size_t h_border, size_t v_border, int selected)
{
    char *output = NULL;
    int k = 0;

    char **args = processArgs(text);

    size_t max_args_size = maxArgsSize(args);
    size_t col = max_args_size + (2 * h_border);
    output = addHead(col, output);

    output = addVBorder(v_border, col, output);

    while (args[k])
    {
        char *color;
        if (k == selected)
            color = BOLD_YELLOW;
        else
            color = RESET;

        output = addLine(args[k], color, h_border, max_args_size, output);
        k++;
    }
    output = addVBorder(v_border, col, output);
    output = addClose(col, output);

    // Free dynamic memory

    int j = 0;
    while (args[j])
    {
        free(args[j]);
        j++;
    }
    free(args);
    return output;
}

char *boxFit(char text[], size_t h_border, size_t v_border)
{
    char *output = NULL;
    int k = 0;

    char **args = processArgs(text);

    size_t max_args_size = maxArgsSize(args);
    size_t col = max_args_size + (2 * h_border);
    output = addHead(col, output);

    output = addVBorder(v_border, col, output);

    while (args[k])
    {
        char *color = RESET;
        output = addLine(args[k], color, h_border, max_args_size, output);
        k++;
    }
    output = addVBorder(v_border, col, output);
    output = addClose(col, output);

    // Free dynamic memory

    int j = 0;
    while (args[j])
    {
        free(args[j]);
        j++;
    }
    free(args);
    return output;
}

void printMenuBox(MENU menu)
{
    printf("%s\n", menu->items[0]);

    char **items = menu->items;

    size_t h_border = menu->h_border;
    size_t v_border = menu->v_border;
    int selected = menu->selected;

    char *output = NULL;
    int k = 0;

    size_t max_args_size = maxArgsSize(items);
    size_t col = max_args_size + (2 * h_border);
    output = addHead(col, output);

    output = addVBorder(v_border, col, output);

    while (items[k])
    {
        char *color;
        if (k == selected)
            color = BOLD_YELLOW;
        else
            color = RESET;

        output = addLine(items[k], color, h_border, max_args_size, output);
        k++;
    }
    output = addVBorder(v_border, col, output);
    output = addClose(col, output);

    // Free dynamic memory

    // int j = 0;
    // while (args[j])
    // {
    //     free(args[j]);
    //     j++;
    // }
    // free(args);

    printf("%s", output);
    free(output);
}

void addMenuItem(MENU menu, char *item)
{
    menu->items[menu->n_item] = strdup(item);
    menu->n_item++;
    menu->items = realloc(menu->items, sizeof(char *) * (menu->n_item + 1));
    menu->items[menu->n_item] = NULL;

    // alloc size for submenu entry
    menu->sub_menus = realloc(menu->sub_menus, sizeof(MENU) * (menu->n_item + 1));
    menu->sub_menus[menu->n_item] = NULL;
}

void addMenuItems(MENU menu, char *items[])
{
    int i = 0;
    while (items[i])
    {
        addMenuItem(menu, items[i]);
        i++;
    }
}

MENU getSubMenu(MENU menu, int index)
{
    printf("VALID SUBMENU AT INDEX [%d]\n", getSelected(menu) - 1);
    return menu->sub_menus[index];
}

void addSubMenu(MENU menu, MENU subMenu, size_t index)
{
    setFather(subMenu, menu);
    menu->sub_menus[index] = subMenu;
}

// free dynamic memory of menu
void freeMenu(MENU m)
{
    int i = 0;
    while (m->items[i])
    {
        free(m->items[i]);
        i++;
    }
    free(m->items);

    // TODO: free memory from sub menus
    // int j = 0;
    // while (m->sub_menus[j])
    // {
    //     freeMenu(m->sub_menus[j]);
    //     j++;
    // }
    // free(m->sub_menus);

    free(m);
}

void setFather(MENU subMenu, MENU menu)
{
    subMenu->father = menu;
}

MENU getFather(MENU menu)
{
    return menu->father;
}

void setHBorder(MENU menu, int newHBorder)
{
    menu->h_border = newHBorder;
}

int getHBorder(MENU menu)
{
    return menu->h_border;
}

void setVBorder(MENU menu, int newVBorder)
{
    menu->v_border = newVBorder;
}

int getVBorder(MENU menu)
{
    return menu->v_border;
}

void setHVBorder(MENU menu, int newHBorder, int newVBorder)
{
    menu->h_border = newHBorder;
    menu->v_border = newVBorder;
}

void setSelected(MENU menu, int newSelected)
{
    menu->selected = newSelected;
}

int getSelected(MENU menu)
{
    return menu->selected;
}

void setNItem(MENU menu, int newNItem)
{
    menu->n_item = newNItem;
}

int getNItem(MENU menu)
{
    return menu->n_item;
}

void contentUp(MENU menu)
{
    if (getSelected(menu) - 1 > 0)
        setSelected(menu, getSelected(menu) - 1);
}

void contentDown(MENU menu)
{
    if (getSelected(menu) + 1 < getNItem(menu))
        setSelected(menu, getSelected(menu) + 1);
}

// int main()
// {
//     MENU caixa = malloc(sizeof(MENU));
//     innitMenu(caixa, " MENU" RED UNICODE_X RESET "\n1. Jogar" GREEN THIN_TICK RESET "\n2. Editar "
//                      "\n3. Sair " RED UNICODE_X RESET,
//               2, 2, 3);
//     printMenu(caixa);

//     freeMenu(caixa);
// }