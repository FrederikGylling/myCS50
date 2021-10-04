""" this is a direct translation from c to python """

def get_number():
    """ get card number from user. Call validate() to get card type """

    # get card number as string
    n = input("Number: ") # get's card number from user

    # convert to integer
    try:
        n = int(n)
    except:
        print("INVALID")
        return

    # test validaity and type
    i = test(n)
    first2 = int(n / pow(10, i - 2))

    # based on digits and starting digits, print type
    if (i == 15 and (first2 == 34 or first2 == 37)):
        print("AMEX")
    elif (i == 16 and (first2 >= 51 and first2 <= 55)):
        print("MASTERCARD")
    elif ((i == 13 or i == 16) and int(first2 / 10) == 4):
        print("VISA")
    else:
        print("INVALID")


def test(n):
    """ validating the checksum as per Luhn's algorithm """
    # initiate variables
    sumby2 = sumplus = iteration = 0

    # alternating for each second digti as per Luhn's algorith, and summing up
    while (n > 0):
        if ((iteration % 2) != 0):
            x = int((n % 10) * 2)
            sumby2 = int(sumby2 + (x / 10) + (x % 10))
        else:
            sumplus = int(sumplus + (n % 10))

        n = n / 10
        n = int(n)
        iteration += 1
    
    print(iteration)
    # validating checksum and return digits if valid, otherwise 0
    if (((sumby2 + sumplus) % 10) == 0):
        return iteration
    else:
        return 0


get_number()
