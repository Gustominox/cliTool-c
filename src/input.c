#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "input.h"
#include "unicode.h"
#include "colors.h"
#include "box.h"
#define clearScreen() printf("\033[1;1H\033[2J")
#define moveCursorTo(x, y) printf("\033[%d;%dH", (y), (x)); // Move cursor to (x, y)

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

// void clearScreen()
// {
//     printf("\033[1;1H\033[2J");
// }

// https://stackoverflow.com/questions/5167269/how-to-get-the-size-of-the-terminal-window-in-a-unix-shell
int getTerminalSize(int *rows, int *cols)
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return -1;
    *rows = w.ws_row;
    *cols = w.ws_col;
    return 0;
}

void menuLoop(MENU menu)
{
    int rows, cols;

    clearScreen();
    printMenuBox(menu);

    char c;
    while ((c = getch()))
    {
        // print menu
        // getTerminalSize(&rows, &cols);
        // printf("%d %d", rows, cols);

        // printf("CHAR: %d\n", c); DEBUG

        switch (c)
        {

        case '\033': // ESC
                     // if the first value is esc

            getch(); // skip the [
            switch (getch())
            {         // the real value
            case 'A': // code for arrow up
                contentUp(menu);
                break;
            case 'B': // code for arrow down
                contentDown(menu);
                break;
            case 'C': // code for arrow right

                break;
            case 'D': // code for arrow left

                break;
            }
            break;
        case '\n': // CHOOSE A SUBMENU

            menu = getSubMenu(menu, 0);

            break;
        default:

            break;
        }

        clearScreen();
        printMenuBox(menu);
    }
}

int main()
{

    MENU caixa = innitMenu();

    MENU caixa2 = innitMenu();

    addSubMenu(caixa, caixa2);


    setHVBorder(caixa, 2, 1);
    // clearScreen();

    addMenuItem(caixa, "   MENU");
    addMenuItem(caixa, "1. Jogar" GREEN THIN_TICK RESET);
    addMenuItem(caixa, "2. Editar ");
    addMenuItem(caixa, "3. Sair " RED UNICODE_X RESET);

    setHVBorder(caixa2, 2, 1);



    menuLoop(caixa);
    // clearScreen();

    // freeMenu(caixa);

    return 0;
}