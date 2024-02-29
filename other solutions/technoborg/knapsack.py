import numpy as np
import math

def readFile(file):
    with open(file) as f:
        # capacity = x
        # sack = [[a1, b1, c1], [a2, b2, c2], [a3, b3, c3]]
        # {x, {{a, b, c}, {d, e, f}, {g, h, i}}}

        array = f.read()[1:-3]
        # x, {{a1, b1, c1}, {a2, b2, c2}, {a3, b3, c3
        capacity = int(array[:array.find(",")])
        array = array[array.find("{{") + 2:].replace("}, ", "").split("{")
        #["a1, b1, c1", "a2, b2, c2", "a3, b3, c3"]
        
        for i, x in enumerate(array):
            array[i] = x.split(", ")
        # [[a1, b1, c1], [a2, b2, c2], [a3, b3, c3]]
        
        sack = np.array(array, dtype=int)
        return sack, capacity

def knapsack(grid, i, c):
    # value = i[x][0], weight = i[x][1] or [x][v, w]
    # grid = np.zeros((len(i)+1, c+1), dtype=int)

    # x is items available to take, y is sack capacity
    for x in range(len(i)+1):
        for y in range(c+1):
            # Fills out all the 0 items, 0 capacity rows/columns w/ 0
            if x == 0 or y == 0:
                grid[x][y] = 0

            # If the weight of the current item is too large, take the value given the previous items
            elif i[x-1][1] > y and i[x-1][2] > 0:
                valueGivenSpace = grid[x-1][y]# knapsack(grid, i[:-x+1], y)
                grid[x][y] = valueGivenSpace
                # grid[x-1][y]

            # Take the max of the value given the previous items or the value of the previous items w/ capacity - current weight + current value
            else:
                i[x-1][2] -= 1
                valueGivenSpace = max(knapsack(grid, i[:-x], y-i[x-1][1])+i[x-1][0], grid[x-1][y])#knapsack(grid, i[:-x+1], y))
                grid[x][y] = valueGivenSpace
                # max(grid[x-1][y], grid[x-1][y-i[x-1][1]]+i[x-1][0])
            
    return grid[len(i)][c] # , grid
    """ First attempt w/ answers:
    if len(i) == 0 or c == 0:
        return 0
    elif i[len(i)-1][1] > c:
        return knapsack(i[:len(i)-2], c)
    else:
        return max(knapsack(i[:len(i)-2], c), knapsack(i[:len(i)-2], c-i[len(i)-1][1])+i[len(i)-1][0])

    1:  39
    2:  52
    3:  80
    4:  104
    5 and on: didn't run
    """

def main():
    correctAnswers = {
        "1":55,
        "2":91,
        "3":97,
        "4":151,
        "5":468,
        "6":875,
        "7":2676,
        "8":8946,
        "9":17672,
        "10":44217,
    }

    cont = True
    while cont:
        file = input("Knapsack File: ")
        sack, capacity = readFile(f"Knapsack Problem\\Test Cases\\{file}.txt")
        print(f"Space available: {capacity}\nSack: {sack}")

        grid = np.zeros((len(sack)+1, capacity+1), dtype=int)

        value = knapsack(grid, sack, capacity)
        #re-include grid here

        print(f"Grid: {grid}n\n"\
              f"Optimal value given a capacity of {capacity}: {value}\n"\
              f"Correct Value: {correctAnswers[file]}\n"\
              f"Program validity: {value == correctAnswers[file]}")

        tf = {"y":True, "n":False, "yes":True, "no":False}
        while True:
            try:
                cont = tf[input("Continue running? (Y/N): ").lower()]
                break
            except:
                print("Only input Y/N")

main()
