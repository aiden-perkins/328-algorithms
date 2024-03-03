
def bf_recursion(matrices, i, j):
    if i == j:
        return 0
    values = []
    for k in range(i, j):
        values.append(
            bf_recursion(matrices, i, k) +
            bf_recursion(matrices, k + 1, j) +
            (matrices[i][0] * matrices[k + 1][0] * matrices[j][1])
        )
    return min(values)


def brute_force(file_path):
    matrices = [tuple(int(i) for i in a.split(', ')) for a in open(file_path).read()[2:-2].split('}, {')]
    return bf_recursion(matrices, 0, len(matrices) - 1)


def dp_recursion(matrices, i, j, cache):
    if i == j:
        return 0
    if cache[i][j]:
        return cache[i][j]
    values = []
    for k in range(i, j):
        values.append(
            dp_recursion(matrices, i, k, cache) +
            dp_recursion(matrices, k + 1, j, cache) +
            (matrices[i][0] * matrices[k + 1][0] * matrices[j][1])
        )
    cache[i][j] = min(values)
    return cache[i][j]


def dynamic_programming_recursion(file_path):
    matrices = [tuple(int(i) for i in a.split(', ')) for a in open(file_path).read()[2:-2].split('}, {')]
    cache = [[0 for _ in range(len(matrices))] for _ in range(len(matrices))]
    return dp_recursion(matrices, 0, len(matrices) - 1, cache)


def dynamic_programming(file_path):
    matrices = [tuple(int(i) for i in a.split(', ')) for a in open(file_path).read()[2:-2].split('}, {')]
    cache = [[0 for _ in range(len(matrices))] for _ in range(len(matrices))]
    for a in range(1, len(matrices)):
        for i in range(len(matrices) - a):
            j = a + i
            values = []
            for k in range(i, j):
                values.append(cache[i][k] + cache[k + 1][j] + (matrices[i][0] * matrices[k + 1][0] * matrices[j][1]))
            cache[i][j] = min(values)
    return cache[0][len(matrices) - 1]
