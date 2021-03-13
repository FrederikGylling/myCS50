#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get users name
    string name = get_string("What's your name? \n");

    // greets user with input name
    printf("Hello, %s\n", name);
}