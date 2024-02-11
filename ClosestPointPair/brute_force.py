import math


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
