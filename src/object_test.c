#include "input.h"
#include "unicode.h"
#include "colors.h"
#include "box.h"

int main()
{

    char ball_art[] =
        "\n       _...----.._"
        "\n     ,:':::::.     `>."
        "\n   ,' |:::::;'     |:::."
        "\n  /    `'::'       :::::"
        "\n /         _____     `::;"
        "\n:         /:::::\\      ` :"
        "\n| ,.     /::FCP::\\       |"
        "\n|;:::.   `::::::;'       |"
        "\n::::::     `::;'      ,. ;"
        "\n \\:::'              ,::::/"
        "\n  \\                 \\:::/"
        "\n   `.     ,:.        :;'"
        "\n     `-.::::::..  _.''"
        "\n        ```----'''";

    char *output = boxFit(ball_art, 0, 0);
    printf("%s", output);

    return 0;
}