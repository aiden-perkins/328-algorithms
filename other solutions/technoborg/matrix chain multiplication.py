import numpy as np

def readFile(file):
    with open(file) as f:
        array = f.read()[2:-2].split("}, {")
        for i, x in enumerate(array):
            array[i] = x.split(", ")
        return np.array(array, dtype=int)

def m(matrices):
    grid = np.zeros((len(matrices), len(matrices)), dtype=int)

    for i in range(len(matrices)):
        for j in range(0, len(matrices)-i):
            if j != j+i:
                minimums = []
                for k in range(j, j+i):
                    cost = matrices[j][0]*matrices[k+1][0]*matrices[j+i][1]
                    minimums.append(grid[j][k] + grid[k+1][j+i] + cost)
                grid[j][j+i] =  int(min(minimums))
        
    return grid, grid[0][len(matrices)-1]
    
def main():
    correctAnswers = {
        "1":2135,
        "2":7722,
        "3":2256,
        "4":15666,
        "5":19525,
        "6":24932,
        "7":35418,
        "8":78735,
        "9":101665,
        "10":142640,
    }
    cont = True

    while cont:
        matrices = readFile(f"Matrix Chain Multiplication\\Test Cases\\{input('Matrix File: ')}.txt")
        print()
        # print(f"Matrices: {matrices}")
        grid, mcm = m(matrices)

        print(f"Grid of Matrix Chain Multiplications: \n{grid}\n"
            f"Minimum registers for matrix multiplication: {mcm}")

        tf = {"y":True, "n":False, "yes":True, "no":False}
        while True:
            try:
                cont = tf[input("Continue running? (Y/N) ").lower()]
                break
            except:
                print("Only input Y/N")
        
main()