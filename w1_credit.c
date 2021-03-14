#include <cs50.h>
#include <stdio.h>
#include <math.h>

// declare helper function
int test(long);

// getting card number and check validity and type
int main(void)
{
    // get card number
    long n = get_long("Card number: ");

    // test validaity and type
    int i = test(n);
    int first2 = n / pow(10, i - 2);

    // based on digits and starting digits, print type
    if (i == 15 && (first2 == 34 || first2 == 37))
    {
        printf("AMEX\n");
    }
    else if (i == 16 && (first2 >= 51 && first2 <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((i == 13 || i == 16) && first2 / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// validating the checksum as per Luhn's algorithm
int test(long n)
{
    // initating varibales
    int sumby2 = 0, sumplus = 0, iteration = 0;

    do
    {
        // alternating for each second digti as er Luhn's algorith, and summing up
        if ((iteration % 2) != 0)
        {
            int x = (n % 10) * 2;
            sumby2 = sumby2 + (x / 10) + (x % 10);
        }
        else
        {
            sumplus = sumplus + (n % 10);
        }
        n = n / 10;
        iteration ++;
    }
    while (n > 0);

    // validating checksum and return digits if valid, otherwise 0
    int valid = ((sumby2 + sumplus) % 10) == 0;
    if (valid)
    {
        return iteration;
    }
    else
    {
        return 0;
    }
}
