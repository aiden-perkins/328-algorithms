import re

with open("Knapsack Problem\\Test Cases\\1 copy.txt", "r") as file:
    data = file.read()

item_strings = re.findall(r'{(.+?)}', data)

weights = []
values = []

for item_str in item_strings:
    item_parts = item_str.split(", ")
    if len(item_parts) == 3:
        weight, value, whatever = map(int, item_parts)
        weights.append(value)
        values.append(weight)

def knapSack(W, wt, val, n):
    K = [[0 for x in range(W + 1)] for x in range(n + 1)]

    for i in range(n + 1):
        for w in range(W + 1):
            if i == 0 or w == 0:
                K[i][w] = 0
            elif wt[i - 1] <= w:
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w])
            else:
                K[i][w] = K[i - 1][w]

    return K[n][W], K

W = 50
n = len(weights)
value, sack = knapSack(W, weights, values, n)
for x in sack:
    print(x)
print(f"{value}")

#1  W 50 = V 55
#2  W 66 = V 91
#3  W 92 = V 97
#4  W 139 = V 151
#5  W 310 = V 468
#6  W 604 = V 875
#7  W 1878 = V 2676
#8  W 6229 = V 8946
#9  W 12607 = V 17672
#10 W 31222 = V 44217 