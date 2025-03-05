#include "input.h"
#include "unicode.h"
#include "colors.h"
#include "box.h"

int main()
{

    MENU caixa = innitMenu();

    MENU caixa2 = innitMenu();

    setHVBorder(caixa, 2, 1);
    // clearScreen();

    addMenuItem(caixa, "   MENU");
    addMenuItem(caixa, "1. Jogar" GREEN THIN_TICK RESET);
    addMenuItem(caixa, "2. Editar ");
    addMenuItem(caixa, "3. Sair " RED UNICODE_X RESET);

    setHVBorder(caixa2, 2, 1);

    addMenuItem(caixa2, "   MENU 2");
    addMenuItem(caixa2, "1. Facil");
    addMenuItem(caixa2, "2. Casual");
    addMenuItem(caixa2, "3. Experiente");

    addSubMenu(caixa, caixa2, 0);

    menuLoop(caixa);

    // freeMenu(caixa);

    return 0;
}