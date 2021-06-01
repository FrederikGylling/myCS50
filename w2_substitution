#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// prototypes
int validate_key(int argc, string argv[], bool validation[]);
void encipher(string key, string plaintext);

int main(int argc, string argv[])
{
    // send key for validation
    bool validation[4];
    validate_key(argc, argv, validation);

    // print to user if validation error
    if (validation[0] == 1 || validation[1] == 1 || validation[2] == 1 || validation[3] == 1)
    {
        if(validation[0] == 1)
        {
            printf("Usage: ./substitution key\n");
        }

        if(validation[1] == 1)
        {
            printf("Key must contain 26 characters.\n");
        }

        if(validation[2] == 1)
        {
            printf("Key must contain alphabetic charactors only.\n");
        }

        if(validation[3] == 1)
        {
            printf("Key must not contain repeating charactors.\n");
        }

        return 1;
    }

    // get plain text from user
    string plaintext = get_string("plaintext: ");

    // send plaintext to be enciphered and printed
    encipher(argv[1], plaintext);

    return 0;
}

int validate_key(int argc, string argv[], bool validation[])
{
    // 1. check if correct arguments at run-time
    if (argc != 2)
    {
        validation[0] = 1;
        return 1;
    }

    // 2. check key length
    if (strlen(argv[1]) != 26)
    {
        validation[1] = 1;
        return 1;
    }

    // 3. check non-alphabetic
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            validation[2] = 1;
            return 1;
        }
    }

    // 4. check for repeating char (case insentitive)
    int repeat[26];
    for (int i = 0, letter = 0; i < 26;  i++)
        {
            letter = (toupper(argv[1][i]) - 65); // take the i position in the key, unify to uppercase, and convert A to 0
            repeat[letter] ++;
            if (repeat[letter] == 2)
                {
                validation[3] = 1;
                return 1;
                }
        }

    return 0;
}

void encipher(string key, string plaintext)
{
    // for each letter, find the substitute
    string enciphertext = plaintext;
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (isalpha(plaintext[i]))
        {
            // which letter of the alphabet is the plain letter
            int plainletter = (toupper(plaintext[i]) - 65);

            // convert that plain letter to the alphabetic order of the key
            char encipherletter = toupper(key[plainletter]);

            // add that to the encipher string in the correct case
            if (islower(plaintext[i]))
            {
                enciphertext[i] = tolower(encipherletter);
            }
            else
            {
                enciphertext[i] = encipherletter;
            }
        }
    }

    printf("ciphertext: %s\n", enciphertext);
}
