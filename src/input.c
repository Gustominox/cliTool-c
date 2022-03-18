#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include "input.h"
#include "unicode.h"
#include "colors.h"
#include "box.h"

char getch()
{
    char buf = 0;
    struct termios old = {0};

    if (tcgetattr(0, &old) < 0) // associa stdin do terminal a struct termios old
        perror("tcsetattr()");

    old.c_lflag &= ~ICANON; // old.c_lflag = (old.c_lflag) & (~(ICANON));
    /*
    This code turns off the ICANON bit.
    The ICANON defines a bit through a mask, e.g. 0x8000 (the ICANON bit is the
    one having value 1, when you apply the bitwise not operator, ~, all bits are
    "inverted" and you have (if the values are 16bit wide) 0x7FFF. If you put in
    bitwise and (&) this value with x, the result is to keep unchanged all bits
    of x matching a "1" bit in the mask 0x7FFF, and "turn off" the bits of x
    matching a "0" bit in the mask, which is exactly the ICANON bit in this specific case.
    */
    /* https://stackoverflow.com/questions/20948621/what-does-mean */

    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");

    if (read(0, &buf, 1) < 0)
        perror("read()");

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

void clearScreen()
{
    printf("\033[1;1H\033[2J");
}

int main()
{

    MENU caixa = malloc(sizeof(MENU));

    innitMenu(caixa, "   MENU\n1. Jogar" GREEN THIN_TICK RESET "\n2. Editar "
                     "\n3. Sair " RED UNICODE_X RESET,
              4,2, 1, 3);
    clearScreen();
    printMenu(caixa);

    char c;
    while ((c = getch()))
    {
        // printf("CHAR: %d\n", c); DEBUG

        if (c == '\033')
        { // if the first value is esc

            getch(); // skip the [
            switch (getch())
            {         // the real value
            case 'A': // code for arrow up
                contentUp(caixa);
                break;
            case 'B': // code for arrow down
                contentDown(caixa);
                break;
            case 'C': // code for arrow right

                break;
            case 'D': // code for arrow left

                break;
            }
        }
        clearScreen();
        printMenu(caixa);
    }
}