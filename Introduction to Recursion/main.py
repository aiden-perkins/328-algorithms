import math
import time


def split_and_solve(points):
    if len(points) < 10:
        brute_min = math.inf
        for i, p1 in enumerate(points):
            for p2 in points[i + 1:]:
                distance = math.dist(p1, p2)
                if brute_min > distance:
                    brute_min = distance
        return brute_min
    middle_idx = len(points) // 2
    new_min = min(split_and_solve(points[:middle_idx]), split_and_solve(points[middle_idx:]))
    left_idx = middle_idx
    left_min = points[middle_idx][0] - new_min
    while points[left_idx][0] >= left_min and left_idx > 0:
        left_idx -= 1
    right_idx = middle_idx
    right_max = points[middle_idx][0] + new_min
    while right_idx < len(points) and points[right_idx][0] <= right_max:
        right_idx += 1
    middle_points = sorted(points[left_idx:right_idx], key=lambda x: x[1])
    for i, p1 in enumerate(middle_points):
        for j in range(1, 3):
            if i + j < len(middle_points):
                distance = math.dist(p1, middle_points[i + j])
                if distance < new_min:
                    new_min = distance
    return new_min


def brute_force(points):
    new_min = math.inf
    for i, p1 in enumerate(points):
        for p2 in points[i + 1:]:
            distance = math.dist(p1, p2)
            if new_min > distance:
                new_min = distance
    return new_min


def solve(file, is_brute_force):
    points = sorted(
        [[float(i) for i in a.split(', ')] for a in open(file).read()[2:-2].split('}, {')],
        key=lambda c: c[0]
    )
    start = time.time()
    if is_brute_force:
        ans = brute_force(points)
    else:
        ans = split_and_solve(points)
    end_time = time.time() - start
    return ans, end_time


if __name__ == '__main__':
    do_brute_force = True
    for file_num in range(11):
        sol, t = solve(f'./Introduction to Recursion/{file_num}.txt', do_brute_force)
        print(f'{file_num}. {round(sol, 3)} | took {round(t, 4)} seconds.')
