import math


def split_and_solve(points):
    if len(points) < 10:
        brute_min = float('inf')
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


def divide_and_conquer(file_path):
    points = sorted(
        [[float(i) for i in a.split(', ')] for a in open(file_path).read()[2:-2].split('}, {')],
        key=lambda c: c[0]
    )
    return round(split_and_solve(points), 3)


def brute_force(file_path):
    points = sorted(
        [[float(i) for i in a.split(', ')] for a in open(file_path).read()[2:-2].split('}, {')],
        key=lambda c: c[0]
    )
    new_min = float('inf')
    for i, p1 in enumerate(points):
        for p2 in points[i + 1:]:
            distance = math.dist(p1, p2)
            if new_min > distance:
                new_min = distance
    return new_min
