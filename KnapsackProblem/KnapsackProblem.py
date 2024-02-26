
def bf_recursion():
    pass


def brute_force(file_path):
    file_contents = open(file_path).read()[1:-3].split(', {')
    capacity = int(file_contents[0])
    bricks = [list(map(int, b.replace('{', '').split(', ')[:-1])) for b in file_contents[1:]]
    return 0


def dp_recursion():
    pass


def dynamic_programming(file_path):
    file_contents = open(file_path).read()[1:-3].split(', {')
    capacity = int(file_contents[0])
    bricks = [list(map(int, b.replace('{', '').split(', ')[:-1])) for b in file_contents[1:]]
    return 0
