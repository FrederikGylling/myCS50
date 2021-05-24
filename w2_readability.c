#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letter(string text);
int count_word(string text);
int count_sentence(string text);
int grading(int letter, int word, int sentence);

int main(void)
{
    string text = get_string("Text: ");

    // call helper functions
    int letter = count_letter(text);
    int word = count_word(text);
    int sentence = count_sentence(text);
    int grade = grading(letter, word, sentence);

    // print grade based on <1 to 16+ grading logic
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// count upper and lower case letters
int count_letter(string text)
{
    int sum = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
            sum ++;
    }
    return sum;
}

// simply count words by counting spaces
int count_word(string text)
{
    int sum = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == ' ')
            sum ++;
    }
    if (sum > 1)
        sum ++;
    return sum;
}

// simply count sentences by recognizing ".", "?", and "!"
int count_sentence(string text)
{
    int sum = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
            sum ++;
    }
    return sum;
}

// helper function that calculate the reading grade based on Coleman-Liau index
int grading(int letter, int word, int sentence)
{
    // takes the average for 100 words and use that for the grading index formula
    float letter_avg = letter * 100.0 / word;
    float sentence_avg = sentence * 100.0 / word;
    // Coleman-Liau index formula
    int grade = round(0.0588 * letter_avg - 0.296 * sentence_avg - 15.8);
    return grade;
}
