
def bf_recursion():
    return 0


def brute_force(file_path):
    matrices = [tuple(int(i) for i in a.split(', ')) for a in open(file_path).read()[2:-2].split('}, {')]
    return bf_recursion()


def dp_recursion():
    return 0


def dynamic_programming_recursion(file_path):
    matrices = [tuple(int(i) for i in a.split(', ')) for a in open(file_path).read()[2:-2].split('}, {')]
    cache = [[0 for _ in range(len(matrices))] for _ in range(len(matrices))]
    return dp_recursion()


def dynamic_programming(file_path):
    matrices = [tuple(int(i) for i in a.split(', ')) for a in open(file_path).read()[2:-2].split('}, {')]
    cache = [[0 for _ in range(len(matrices))] for _ in range(len(matrices))]
    for i in range(len(matrices)):
        for j in range(len(matrices) - i):
            pass
    return 0
