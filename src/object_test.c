#include "input.h"
#include "unicode.h"
#include "colors.h"
#include "box.h"

int main()
{

    char * output = makeBox("TEST TEST TEST\nTEST TEST\nTEST\n", 0, 0, 1);
    printf("%s",output);
    
    return 0;
}