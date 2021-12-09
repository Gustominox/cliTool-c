#include <unistd.h>
#include <termios.h>

char getch()
{
    char buf = 0;
    struct termios old = {0};

    if (tcgetattr(0, &old) < 0) // associa stdin do terminal a struct termios old
        perror("tcsetattr()");

    old.c_lflag &= ~ICANON; // old.c_lflag = (old.c_lflag) & (~(ICANON));
    /*
    The code turns off the ICANON bit. 
    The ICANON defines a bit through a mask, e.g. 0x8000 (the ICANON bit is the 
    one having value 1, when you apply the bitwise not operator, ~, all bits are
    "inverted" and you have (if the values are 16bit wide) 0x7FFF. If you put in
    bitwise and (&) this value with x, the result is to keep unchanged all bits 
    of x matching a "1" bit in the mask 0x7FFF, and "turn off" the bits of x 
    matching a "0" bit in the mask, which is exactly the ICANON bit in this specific case.
    */ /* https://stackoverflow.com/questions/20948621/what-does-mean */

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

int main()
{
    char c;
    while (c = getch())
    {
        printf("CHAR: %d\n", c);
    }
}