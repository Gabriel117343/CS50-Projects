#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);
int get_height(void);

int main(void)
{

    int n = get_height();

    for (int i = 1; i <= n; i++)
    {
        print_row(n - i, i);
    }
}

int get_height(void)
// Note: This function only have the unique responsability of handle the user-input
{
    int new_height;
    do
    {
        new_height = get_int("Height 1-8: ");
    }
    while (new_height < 1 || new_height > 8);

    return new_height;
}

void print_row(int spaces, int bricks)
{

    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}
