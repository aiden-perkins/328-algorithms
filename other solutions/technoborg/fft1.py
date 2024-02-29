import numpy as np
import time as t

def readFile(file):
    with open(file) as f:
        return np.array(f.read()[1:-1].replace(" ", "").split(","), dtype=int)
    
def maxSubSum(seq, l, r):
    """# Base Case
    fastTime = t.time()

    if len(seq) <= 2:
        if sum(seq) > max(seq):
            return sum(seq)
        return max(seq)

    # Split
    fourth = len(seq) // 4
    seqLeft = maxSubSum(seq[:2*fourth])
    seqRight = maxSubSum(seq[2*fourth:])
    seqMid = maxSubSum(seq[fourth:3*fourth])
    
    print("--- Recursive time in %s seconds ---" % (t.time() - fastTime))
    return max(seqLeft, seqMid, seqRight)"""

    # Base Case
    if l > r:
        return float("-inf")
    if l == r:
        return seq[l]
    
    # Mid split for recursion
    mid = (l + r) // 2

    return max(maxSubSum(seq, l, mid-1), maxSubSum(seq, mid+1, r), maxCrossSum(seq, l, mid, r))

def maxCrossSum(seq, l, m, r):
    sm = 0
    leftSum = float("-inf")
    for i in range(m, l-1, -1):
        sm += seq[i]
        
        if sm > leftSum:
            leftSum = sm

    sm = 0
    rightSum = float("-inf")
    for i in range(m, r+1):
        sm += seq[i]

        if sm > rightSum:
            rightSum = sm

    return max(leftSum + rightSum - seq[m], leftSum, rightSum)

def subSum(seq):
    slowTime = t.time()
    bestSum = float("-inf")
    curSum = 0

    for x in seq:
        curSum = max(x, curSum + x)
        bestSum = max(curSum, bestSum)
    
    print("--- O(n) time in %s seconds ---" % (t.time() - slowTime))
    return bestSum

def main():
    cont = True

    while cont:
        sequence = readFile("Fast Fourier Transformation\\Test Cases\\" + input("Sequence File: ") + ".txt")

        maxSlow = subSum(sequence)
        fastTime = t.time()
        max = maxSubSum(sequence, 0, len(sequence)-1)
        print("--- O(n log n) time in %s seconds ---" % (t.time() - fastTime))

        #print(sequence)
        print(f"Correct Max: {maxSlow}")
        print(f"Max: {max}")

        valid = False
        while not valid: 
            val = run = input("Continue running? (Y/N) ").upper()
            if val == "YES" or val == "Y":
                cont = True
                valid = True
                continue
            elif val == "NO" or val == "N":
                cont = False
                valid = True
            else:
                print("Invalid input - should be a 'Yes' or 'No'.")

main()

"""
Answers:
    1.  9
    2.  23
    3.  58
    4.  752
    5.  1640
    6.  11973
    7.  12537
    8.  44846
    9.  63133
    10. 140246
"""