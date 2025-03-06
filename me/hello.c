#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Según lo explicado en clase, entiendo que la siguiente linea bloqueda el código hasta que se ingrese el nombre
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}
