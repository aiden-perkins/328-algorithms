import numpy as np
import math

def readFile(file):
    with open(file) as f:
        # {k, {a, b, c, d, e, f, g, h, i}}
        # k, {a, b, c, d, e, f, g, h, i
        array = f.read()[1:-2]
        index = array.find("{") + 1
        k = int(array[:array.find(",")])
        return np.array(array[index:].replace(" ", "").split(","), dtype=int), array[index:].replace(" ", "").split(","), k

def selectNP(L, k):
    # NumPy is broken fast so you can just run these two lines and get the answer lol
    L.sort()
    return L[k-1]
    
    """ OG code
    # Base case
    if len(L) <= 100:
        L.sort()
        return L[k-1]    

    # Split into groups of 5
    remainder = len(L) % 5
    if remainder != 0:
        medianGroups = L[:-remainder].reshape((len(L)//5, 5))
        remainingGroup = np.array(L[-remainder:])
    else:
        medianGroups = L.reshape((len(L)//5, 5))
    
    # Find the median of each group
    # Make a new list with every median
    if 'remainingGroup' in locals():
        m = np.zeros(len(L)//5 + 1)
    else:
        m = np.zeros(len(L)//5)

    for x, median in enumerate(medianGroups):
        m[x] = selectNP(median, 3)
    if 'remainingGroup' in locals():
        m[-1] = selectNP(remainingGroup, remainder//2)
    
    # Find the median of the medians M = selectNP({m}, len(L)//10)
    M = selectNP(m, len(L)//10)

    # Partition L into L_1 < M, L_2 = M, L_3 > M and determine the position of M M_i.
    M_i = np.where(L == M)
    L_1 = L[:M_i[0][0]]
    L_2 = L[M_i[0][0]]
    L_3 = L[M_i[0][0]+1:]

    # If k = M_i, return M. 
    if k == M_i[0][0]:
        return M
    
    # If k < M_i, return selectNP(L_1, k)
    if k < M_i[0][0]:
        return selectNP(L_1, k)
    
    # If k > M_i, return selectNP(L_3, k - len(L_1) - len(L_2))
    if k > M_i[0][0]:
        return selectNP(L_3, k - len(L_1) - 1)"""

def select(L, k):
    # Base case
    if len(L) <= 100:
        L.sort()
        return L[k-1]

    # Split into groups of 5
    fives = []
    for i, x in enumerate(L):
        if (i+1)*5 < len(L):
            fives.append([L[i*5:(i+1)*5]])
        else:
            if len(L) % 5 != 0:
                fives.append([L[-(len(L)%5):]])
            break

    # Find the median of each group
    # Make a new list with every median
    m = []
    for x, med in enumerate(fives):
        if len(med[0]) == 5: 
            m.append(select(med[0], 3))
        else: 
            m.append(select(med[0], math.ceil(len(med)/2)))

    # Find the median of the medians M = select({m}, len(L)//10)
    M = select(m, len(L)//10)

    # Partition L into L_1 < M, L_2 = M, L_3 > M and determine the position of M M_i.
    L_1 = []
    L_2 = [M]
    L_3 = []
    for x in L:
        if x < M:
            L_1.append(x)
        elif x > M:
            L_3.append(x)

    M_i = len(L_1)+1
    
    # If k = M_i, return M. 
    if k == M_i:
        return M

    # If k < M_i, return select(L_1, k)
    if k < M_i:
        return select(L_1, k)

    # If k > M_i, return select(L_3, k - len(L_1) - len(L_2))
    if k > M_i: 
        return select(L_3, k - len(L_1) - len(L_2))

def main():
    # Dictionary to check the correct answers from
    correctAnswers = {
        "1":-1691156564,
        "2":-707753914,
        "3":225415872,
        "4":676302880,
        "5":-1404858153,
        "6":120123075,
        "7":-1736541041,
        "8":428105114,
        "9":-415622866,
        "10":353368082
    }

    cont = True
    while cont:
        # Reads through the given file and prints out the list and index to be found
        file = input("List File: ")
        L_np, L, k = readFile(f"Deterministic Order Selection\\Test Cases\\{file}.txt")

        # Changes the values of L to int (idk where else to do it lol)
        for i, x in enumerate(L):
            L[i] = int(x)

        print(f"NumPy List: {L_np}")
        ### print(f"List: {L}")
        print(f"Index: {k}\n")

        # Gives the algorithm and correct answer of the given list
        valueNP = selectNP(L_np, k)
        value = select(L, k)
        print(f"Value at index {k} of the sorted NumPy List: {valueNP}")
        print(f"Index of value {valueNP} in NumPy List: {L.index(valueNP)}\n")

        print(f"Value at index {k} of the sorted List: {value}")
        print(f"Index of value {value} in List: {L.index(value)}\n")

        print(f"Index difference: {L.index(value) - L.index(valueNP)}\n")

        print(f"Correct value: {correctAnswers[file]}")
        print(f"Correct output: {valueNP == correctAnswers[file]}, {value == correctAnswers[file]}")

        # Check to continue running; error if not given y/n
        tf = {"y":True, "n":False, "yes":True, "no":False}
        cont = tf[input("Continue running? (Y/N): ").lower()]
        
main()