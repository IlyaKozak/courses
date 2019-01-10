from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    listA = a.split('\n')
    listB = b.split('\n')
    listC = []

    # comparing lines of listA and listB
    for line in listA:
        if line in listB and line not in listC:
            listC.append(line)
    return listC


def sentences(a, b):
    """Return sentences in both a and b"""
    listA = sent_tokenize(a)
    listB = sent_tokenize(b)
    listC = []

    # comparing sentences of listA and listB
    for sentence in listA:
        if sentence in listB and sentence not in listC:
            listC.append(sentence)
    return listC


def slicing(string, n):
    """ Slicing string to list of n-characters strings (without duplicates) """
    listOfSlices = []

    # making list of string slices (substr)
    for i in range(0, len(string) - n + 1):
        substr = string[i:i+n]
        if substr not in listOfSlices:
            listOfSlices.append(substr)
    return listOfSlices


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    listA = slicing(a, n)
    listB = slicing(b, n)
    listC = []

    # comparing substrings of listA and listB
    for substring in listA:
        if substring in listB:
            listC.append(substring)
    return listC
