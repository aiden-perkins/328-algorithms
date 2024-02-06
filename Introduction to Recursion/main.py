import math
import time


def middle_coords(min_distance, matrix):
    trimmed = []
    new_m = min_distance
    for coord in matrix:
        if abs(matrix[len(matrix) // 2][0] - coord[0]) <= min_distance:
            trimmed.append(coord)
    trimmed = sorted(trimmed, key=lambda point: point[1])
    for i, coord1 in enumerate(trimmed):
        for j in range(1, 3):
            if i + j < len(trimmed):
                distance1 = math.dist(coord1, trimmed[i + j])
                if distance1 < new_m:
                    new_m = distance1
    return new_m


def distance(matrix):
    m = math.inf
    for coord1 in matrix:
        for coord2 in matrix:
            if coord1 != coord2:
                distance = math.dist(coord1, coord2)
                if m > distance:
                    m = distance
    return abs(m)


def find_closest(matrix):
    right_s = (len(matrix) // 2)
    right_e = len(matrix)
    left_s = 0
    left_e = len(matrix) // 2
    if left_e - left_s > 3:
        left_m = find_closest(matrix[left_s:left_e])
    else:
        left_m = distance(matrix[left_s:left_e])
    if right_e - right_s > 3:
        right_m = find_closest(matrix[right_s:right_e])
    else:
        right_m = distance(matrix[right_s:right_e])
    m_m = min(right_m, left_m)
    return min(m_m, middle_coords(m_m, matrix))


def brute_force_yay(matrix):
    small = math.inf
    for coord1 in matrix:
        for coord2 in matrix:
            if coord1 != coord2:
                distance = math.dist(coord1, coord2)
                if small > distance:
                    small = distance
    return small


def solve(file, brute_force):
    f = open(file)
    matrix = f.read().split('}, {')
    matrix[0] = matrix[0][2:]
    matrix[len(matrix)-1] = matrix[len(matrix)-1][:-2]
    matrix = sorted([[float(i) for i in a.split(', ')] for a in matrix], key=lambda c: c[0])
    f.close()
    
    start = time.time()
    if brute_force:
        ans = brute_force_yay(matrix)
    else:
        ans = find_closest(matrix)
    end_time = time.time() - start
    return ans, end_time


if __name__ == '__main__':
    do_brute_force = False
    for file_num in range(11):
        sol, t = solve(f'{file_num}.txt', do_brute_force)
        print(f'{file_num}. {round(sol, 3)} | took {round(t, 4)} seconds.')
