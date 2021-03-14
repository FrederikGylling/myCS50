#include <cs50.h>
#include <stdio.h>

// declare helper function
void space(int x);
void brick(int y);

// get height from user and print pyramid accordingly
int main(void)
{
    // prompt user for height between 1 and 8, inclusive
    printf("Please, input a height [1,9[\n");
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    // print out the pyramid
    // s variable to keep track of spaces and b variable to keep track of bricks
    int s = h;
    for(int b = 1; (b <= h); b++)
    {
        space(s - 1);
        brick(b);
        space(2);
        brick(b);
        printf("\n");
        s--;
    }
}

// helper function printng spcaes
void space(int x)
{
    while (x > 0)
    {
        printf(" ");
        x--;
    }
}

// helper function printng bricks
void brick(int y)
{
    while (y > 0)
    {
        printf("#");
        y--;
    }
}
