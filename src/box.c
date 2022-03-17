#include "box.h"
#include "unicode.h"
#include "colors.h"
#include "fruits.h"
#include "ball.h"


char *strcatrealloc(char *str1, char str2[])
{
    size_t str1len = 0;
    if (str1)
    {
        str1len = strlen(str1);
    }
    size_t str2len = strlen(str2);

    // char *strdest = (char *)malloc(sizeof(char));
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

char *printHead(size_t col, char *output)
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

char *printClose(size_t col, char *output)
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

char *printHBorder(size_t h_border, char *output)
{
    for (size_t i = 0; i < h_border; i++)
        output = strcatrealloc(output, " ");
    return output;
}

char *printEmptyLine(size_t col, char *output)
{
    output = strcatrealloc(output, V_L);
    for (size_t i = 0; i < col; i++)
        output = strcatrealloc(output, " ");
    output = strcatrealloc(output, V_L);
    output = strcatrealloc(output, "\n");
    return output;
}

char *printVBorder(size_t v_border, size_t col, char *output)
{
    for (size_t i = 0; i < v_border; i++)
        output = printEmptyLine(col, output);
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

char *printLine(char line[], size_t h_border, size_t maxArgsSize, char *output)
{
    output = strcatrealloc(output, V_L);
    output = printHBorder(h_border, output);
    output = strcatrealloc(output, line);
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
    output = printHBorder(buffer, output);
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
char *makeBox(char text[], size_t h_border, size_t v_border)
{
    char *output = NULL;
    char *text_p = strdup(text);
    char *text_p_free = text_p;
    char **args = malloc(sizeof(char *) * 100);
    char *token;
    int i = 0, k = 0;
    while ((token = strtok_r(text_p, "\n", &text_p)))
    {
        args[i] = strdup(token);
        i++;
    }
    args[i] = NULL;
    size_t max_args_size = maxArgsSize(args);
    size_t col = max_args_size + (2 * h_border);
    output = printHead(col, output);

    output = printVBorder(v_border, col, output);

    while (args[k])
    {
        output = printLine(args[k], h_border, max_args_size, output);
        k++;
    }
    output = printVBorder(v_border, col, output);
    output = printClose(col, output);

    // Free dynamic memory
    free(text_p_free);
    int j = 0;
    while (args[j])
    {
        free(args[j]);
        j++;
    }
    free(args);
    return output;
}

int main()
{



    char *str = makeBox(" MENU" RED UNICODE_X RESET
                  "\n1. Jogar" GREEN THIN_TICK RESET
                  "\n2. Editar "
                  "\n3. Sair " RED UNICODE_X UNICODE_X RESET,
                  4, 4);
    printf("%s", str);
    free(str);
}