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
"\n        ```----'''" ;


    char * output = makeBox(ball_art, 0, 0, 6);
    printf("%s",output);
    
    return 0;
}