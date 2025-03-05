#ifndef INPUT_H_
#define INPUT_H_

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define clearScreen() printf("\033[1;1H\033[2J")
#define moveCursorTo(x, y) printf("\033[%d;%dH", (y), (x)); // Move cursor to (x, y)


char getch();



#endif // INPUT_H_
