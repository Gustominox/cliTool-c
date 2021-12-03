#include "box.h"
#include "unicode.h"
#include "colors.h"
#include "fruits.h"
#include "ball.h"

void printHead(size_t col, FILE *output)
{

    fprintf(output, T_L_A);
    for (size_t i = 0; i < col; i++)
    {
        fprintf(output, H_L);
    }
    fprintf(output, T_R_A);
    fputc('\n', output);
}

void printClose(size_t col, FILE *output)
{

    fprintf(output, B_L_A);
    for (size_t i = 0; i < col; i++)
    {
        fprintf(output, H_L);
    }
    fprintf(output, B_R_A);
    fputc('\n', output);
}

void printHBorder(size_t h_border, FILE *output)
{
    for (size_t i = 0; i < h_border; i++)
        fprintf(output, " ");
}

void printEmptyLine(size_t col, FILE *output)
{
    fprintf(output, V_L);
    for (size_t i = 0; i < col; i++)
        fprintf(output, " ");
    fprintf(output, V_L);
    fputc('\n', output);
}

void printVBorder(size_t v_border, size_t col, FILE *output)
{
    for (size_t i = 0; i < v_border; i++)
        printEmptyLine(col, output);
}

size_t strlen_unicode(char string[])
{
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

void printLine(char line[], size_t h_border, size_t maxArgsSize, FILE *output)
{
    fprintf(output, V_L);
    printHBorder(h_border, output);
    fprintf(output, "%s", line);
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
    printHBorder(buffer, output);
    fprintf(output, V_L);
    fputc('\n', output);
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
void makeBox(char text[], size_t h_border, size_t v_border, FILE *output)
{
    char *text_p = strdup(text);
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
    printHead(col, output);
    printVBorder(v_border, col, output);
    while (args[k])
    {
        printLine(args[k], h_border, max_args_size, output);
        k++;
    }
    printVBorder(v_border, col, output);
    printClose(col, output);
}

int main()
{
    // printf("TMH: %d", strlen_unicode(BOLD_CYAN));

    printf(BOLD_BLUE);

    makeBox(" MENU" RED UNICODE_X BOLD_BLUE
             "\n1. Jogar" GREEN THIN_TICK BOLD_BLUE
             "\n2. Editar "
             "\n3. Sair " RED UNICODE_X UNICODE_X BOLD_BLUE,
             2, 1, stdout);
    printf(RESET);

    makeBox(fruits[50],
             2, 6, stdout);
    makeBox(ball,
             2, 2, stdout);
}