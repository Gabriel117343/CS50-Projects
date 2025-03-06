#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate how many quarters you should give customer
    int quarters = calculate_quarters(cents);
    printf("%d\n", quarters);
}

int calculate_quarters(int cents)
{
    // Calculate how many quarters you should give customer
    int quarters = cents / 25;
    // This represente remainder of divison, then change the cents with it
    cents %= 25;

    int dimes = cents / 10;
    cents %= 10;

    int nickels = cents / 5;
    cents %= 5;

    // The remainder is equal to pennies
    int pennies = cents;

    // finally all results are added together
    return quarters + dimes + nickels + pennies;
}
