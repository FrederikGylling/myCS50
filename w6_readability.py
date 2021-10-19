import re

def readability():
    """
    get input from user and define the readiability score
    helper function that calculate the reading grade based on Coleman-Liau index
    Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8
    where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    """

    t = input("Text: ") # get's input from user

    # count letter, word, and sentence based on input text
    letter = len(re.findall(r"[a-zA-Z]", t))
    word = len(re.findall(r"[a-zA-Z]+\'?[a-zA-Z]*", t))
    sentence = len(re.findall(r'[!?.]+', t))
    #print(letter, word, sentence)

    # takes the average for 100 words and use that for the formula
    letter_avg = letter * 100 / word
    sentence_avg = sentence * 100 / word

    # Coleman-Liau index formula
    #print(0.0588 * letter_avg - 0.296 * sentence_avg - 15.8)
    grade = round(0.0588 * letter_avg - 0.296 * sentence_avg - 15.8)
    print(grade)
    
    # print grade based on <1 to 16+ grading logic
    if (grade < 1):
        print("Before Grade 1")
    elif (grade > 16):
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

readability()
