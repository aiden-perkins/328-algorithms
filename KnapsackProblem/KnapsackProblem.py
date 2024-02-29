import sys


def bf_recursion(bricks, capacity):
    if len(bricks) == 0 or capacity == 0:
        return 0
    if bricks[-1][1] > capacity:
        return bf_recursion(bricks[:-1], capacity)
    return max(bf_recursion(bricks[:-1], capacity), bf_recursion(bricks[:-1], capacity - bricks[-1][1]) + bricks[-1][0])


def brute_force(file_path):
    file_contents = open(file_path).read()[1:-3].split(', {')
    capacity = int(file_contents[0])
    bricks = [list(map(int, b.replace('{', '').split(', ')[:-1])) for b in file_contents[1:]]
    return bf_recursion(bricks, capacity)


def dp_recursion(bricks, capacity, cache, bricks_size):
    if bricks_size == 0 or capacity == 0:
        return 0
    if cache[capacity][bricks_size] != 0:
        return cache[capacity][bricks_size]
    if bricks[bricks_size - 1][1] > capacity:
        cache[capacity][bricks_size] = dp_recursion(bricks, capacity, cache, bricks_size - 1)
        return cache[capacity][bricks_size]
    first = dp_recursion(bricks, capacity, cache, bricks_size - 1)
    second = dp_recursion(
        bricks, capacity - bricks[bricks_size - 1][1], cache, bricks_size - 1
    ) + bricks[bricks_size - 1][0]
    if first > second:
        cache[capacity][bricks_size] = first
    else:
        cache[capacity][bricks_size] = second
    return cache[capacity][bricks_size]


def dynmaic_programming_recursion(file_path):
    # This solution works in solving the problem, however due to python's built in recursion limit, which we
    # cannot change, this will fail the 10th file and crash, it gets 0-9 correct though slightly slower.
    file_contents = open(file_path).read()[1:-3].split(', {')
    capacity = int(file_contents[0])
    bricks = [list(map(int, b.replace('{', '').split(', ')[:-1])) for b in file_contents[1:]]
    cache = [[0 for _ in range(len(bricks) + 1)] for _ in range(capacity + 1)]
    sys.setrecursionlimit(len(bricks) + 5)
    return dp_recursion(bricks, capacity, cache, len(bricks))


def dynamic_programming(file_path):
    file_contents = open(file_path).read()[1:-3].split(', {')
    capacity = int(file_contents[0])
    bricks = [list(map(int, b.replace('{', '').split(', ')[:-1])) for b in file_contents[1:]]
    cache = [[0 for _ in range(len(bricks) + 1)] for _ in range(capacity + 1)]
    for b_i in range(len(bricks) + 1):
        for c in range(capacity + 1):
            if b_i == 0 or c == 0:
                cache[c][b_i] = 0
            elif bricks[b_i - 1][1] > c:
                cache[c][b_i] = cache[c][b_i - 1]
            else:
                first = cache[c][b_i - 1]
                second = cache[c - bricks[b_i - 1][1]][b_i - 1] + bricks[b_i - 1][0]
                if first > second:
                    cache[c][b_i] = first
                else:
                    cache[c][b_i] = second
    return cache[capacity][len(bricks)]
