#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_key(string s);
char encrypt_char(char c, int key);

int main(int argc, string argv[])
{
    // Ensure the program is run with exactly one command-line argument
    if (argc != 2 || !is_valid_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert the key from string to int
    int key = atoi(argv[1]);

    // Prompt the user for plaintext 
    string plaintext = get_string("plaintext: ");

    // Display the ciphertext header
    printf("ciphertext: ");

    // For each character in the plaintext, print its encrypted version
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        printf("%c", encrypt_char(plaintext[i], key));
    }
    printf("\n");
    return 0;
}

// Check if the key consists only of digits
bool is_valid_key(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Encrypt a single character using Caesar cipher rotation
char encrypt_char(char c, int key)
{
    if (isupper(c))
    {
        return ((c - 'A' + key) % 26) + 'A';
    }
    else if (islower(c))
    {
        return ((c - 'a' + key) % 26) + 'a';
    }
    else
    {
        return c;
    }
}
