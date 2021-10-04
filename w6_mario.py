def answer():
    """ get input from user. Call draw() with input """

    n = input("Height: ") # get's input from user
    
    try:
        n = int(n)
    except:
        answer()
        return

    if n in range(1,9):
        draw(n, n) # call draw() with input
    else:
        answer()


def draw(n, H):
    """ based on n and H(height), draws a double half-pyramid recursively """

    # base case for recursive function
    if n == 0:
        return

    # call function recusively
    draw(n-1, H)

    # print out row of pyramid based on n and H(eight)
    print(" " * (H - n), end="")
    print("#" * n, end="")
    print(" " * 2, end="")
    print("#" * n, end="")
    print() #print next line

answer()
