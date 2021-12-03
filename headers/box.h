#ifndef BOX_H_
#define BOX_H_

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void printHead(size_t col, FILE *output);

void printClose(size_t col, FILE *output);

void printHBorder(size_t h_border, FILE *output);

void printEmptyLine(size_t col, FILE *output);

void printVBorder(size_t v_border, size_t col, FILE *output);

size_t strlen_unicode(char string[]);

void printLine(char line[], size_t h_border, size_t maxArgsSize, FILE *output);

size_t maxArgsSize(char **args);

void makeBox(char text[], size_t h_border, size_t v_border, FILE *output);


#endif // BOX_H_
