""" Matches DNA sequence with DNA database """

import csv
from sys import argv, exit

def main():

    # Ensure correct usage
    if len(argv) != 3:
        exit("Usage: python dna.py data.csv sequence.txt")

    # Read data from data source file
    dbFile = open(argv[1])
    db_reader = csv.DictReader(dbFile) # read the data to a dictionairy
    strs = db_reader.fieldnames[1:] # read the headers (besides name) to a list of STRs

    # read DNA sequence from file
    with open(argv[2]) as dnaFile:
        dna = dnaFile.read()

    # count number of consecutive occurances of STR in DNA sequence and add to a dictionairy
    dna_id = {}
    for str in strs:
        dna_id[str] = consec_occur(str, dna)

    # check if dna_id match row in database
    for person in db_reader:

        # return name of person if dna_id match
        if dna_match(strs, dna_id, person):
            print(f"{person['name']}")
            dbFile.close()
            return

    # if there is no match
    print("No match")
    dbFile.close()
    return

def consec_occur(str, dna):
    i = 0
    while str*(i+1) in dna:
        i += 1
    return i

def dna_match(strs, dna_id, person):
    for str in strs:
        if dna_id[str] != int(person[str]):
            return False
    return True

if __name__ == "__main__":
    main()
