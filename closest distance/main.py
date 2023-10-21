import time
import sys
#sys.setrecursionlimit(10 ** 3)

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
                distance1 = (((coord1[0] - trimmed[i + j][0]) ** 2) + ((coord1[1] - trimmed[i + j][1]) ** 2)) ** (1/2)
                if distance1 < new_m:
                    new_m = distance1
    return new_m

def distance(matrix):
    m = -100
    for coord1 in matrix:
        for coord2 in matrix:
            if coord1 != coord2:
                distance = (((coord1[0] - coord2[0]) ** 2) + ((coord1[1] - coord2[1]) ** 2)) ** (1/2)
                if m == -100 or m > distance:
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
    small = -1
    for coord1 in matrix:
        for coord2 in matrix:
            if coord1 != coord2:
                distance = (((coord1[0] - coord2[0]) ** 2) + ((coord1[1] - coord2[1]) ** 2)) ** (1/2)
                if small == -1 or small > distance:
                    small = distance
                    print(small)
    return small

def smallest_distance(file):
    f = open(file, 'r')
    matrix = f.read().split('}, {')
    matrix[0] = matrix[0][2:]
    matrix[len(matrix)-1] = matrix[len(matrix)-1][:-2]
    matrix = sorted([[float(i) for i in a.split(', ')] for a in matrix], key=lambda c: c[0])
    start = time.time()
    a = find_closest(matrix)
    print(f'File {file} is {a} and it took {time.time() - start} seconds')
    f.close()
    """
    start = time.time()
    b = brute_force_yay(matrix)
    print(f'Brute force for file {file} is {b} and it took {time.time() - start} seconds')
    """

smallest_distance('1.txt')
smallest_distance('6.txt')
smallest_distance('9.txt')
smallest_distance('0.txt')
"""
"""


