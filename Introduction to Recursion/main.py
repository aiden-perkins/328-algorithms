import math
import time


def split_and_solve(points):
    if len(points) < 4:
        brute_min = math.inf
        for i, p1 in enumerate(points):
            for p2 in points[i + 1:]:
                distance = math.dist(p1, p2)
                if brute_min > distance:
                    brute_min = distance
        return brute_min
    middle_idx = len(points) // 2
    new_min = min(split_and_solve(points[:middle_idx]), split_and_solve(points[middle_idx:]))
    # Now do middle solve



def brute_force(points):
    new_min = math.inf
    for i, p1 in enumerate(points):
        for p2 in points[i + 1:]:
            distance = math.dist(p1, p2)
            if new_min > distance:
                new_min = distance
    return new_min


def solve(file, do_brute_force):
    points = sorted(
        [[float(i) for i in a.split(', ')] for a in open(file).read()[2:-2].split('}, {')],
        key=lambda c: c[0]
    )
    start = time.time()
    if do_brute_force:
        ans = brute_force(points)
    else:
        ans = split_and_solve(points)
    end_time = time.time() - start
    return ans, end_time


if __name__ == '__main__':
    brute_force = False
    for file_num in range(11):
        sol, t = solve(f'{file_num}.txt', brute_force)
        print(f'{file_num}. {round(sol, 3)} | took {round(t, 4)} seconds.')
