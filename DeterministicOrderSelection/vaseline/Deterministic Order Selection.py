import math


f = "1.txt"

def read_file(file):
    """ Reads a file and returns a list of integers """
    with open(file) as f:
        # {k, {a, b, c, d, e, f, g, h, i}}
        # k, {a, b, c, d, e, f, g, h, i
        array = f.read()[1:-2]
        index = array.find("{") + 1
        k = int(array[:array.find(",")])
        return array[index:].replace(" ", "").split(","), k

def index_finder(integer):
    pass


def select(L, k):
    # Base case
    if len(L) <= 100:
        L.sort()
        return L[k - 1]

    # Split into groups of 5
    fives = []
    for i, x in enumerate(L):
        if (i + 1) * 5 < len(L):
            fives.append([L[i * 5:(i + 1) * 5]])
        else:
            if len(L) % 5 != 0:
                fives.append([L[-(len(L) % 5):]])
            break

    # Find the median of each group
    # Make a new list with every median
    m = []
    for x, med in enumerate(fives):
        if len(med[0]) == 5:
            m.append(select(med[0], 3))
        else:
            m.append(select(med[0], math.ceil(len(med) / 2)))

    # Find the median of the medians M = select({m}, len(L)//10)
    M = select(m, len(L) // 10)

    # Partition L into L_1 < M, L_2 = M, L_3 > M and determine the position of M M_i.
    L_1 = []
    L_2 = [M]
    L_3 = []
    for x in L:
        if x < M:
            L_1.append(x)
        elif x > M:
            L_3.append(x)

    M_i = len(L_1) + 1

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
        "1": -1691156564,
        "2": -707753914,
        "3": 225415872,
        "4": 676302880,
        "5": -1404858153,
        "6": 120123075,
        "7": -1736541041,
        "8": 428105114,
        "9": -415622866,
        "10": 353368082
    }

    cont = True
    while cont:
        # Reads through the given file and prints out the list and index to be found
        file = input("List File: ")
        f = f"{file}.txt"
        L, k = (read_file(f))
        # Changes the values of L to int (idk where else to do it lol)
        for i, x in enumerate(L):
            L[i] = int(x)
        print(f"NumPy List: {L}")
        ### print(f"List: {L}")
        print(f"Index: {k}")

        # Gives the algorithm and correct answer of the given list
        #                   valueNP = selectNP(L, k)
        value = select(L, k)
        #                   print(f"Value at index {k} in the NunPy List: {valueNP}")
        print(f"Value at index {k} in List: {value}")
        print(f"Correct value: {correctAnswers[file]}")
        #                   print(f"Correct output: {valueNP == correctAnswers[file]}, {value == correctAnswers[file]}")

        # Check to continue running; error if not given y/n
        tf = {"y": True, "n": False, "yes": True, "no": False}
        cont = tf[input("Continue running? (Y/N): ").lower()]

main()
