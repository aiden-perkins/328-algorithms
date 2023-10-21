import time
import math
import numpy as np

def display_matrix(matrix):
    s = ''
    for row in matrix:
        s += ' '.join(str(i) for i in row) + '\n'
    print(s)

def total(matrix):
    t = 0
    for row in matrix:
        for item in row:
            t += item
    return t

def read_file(file):
    f = open(file, 'r')
    matrix = f.read().split('}, {')
    matrix[0] = matrix[0][2:]
    matrix[len(matrix)-1] = matrix[len(matrix)-1][:-2]
    matrix = [[int(i) for i in a.split(', ')] for a in matrix]
    f.close()
    return matrix

def brute(matrixA, matrixB):
    p = (matrixA[0][0] + matrixA[1][1]) * (matrixB[0][0] + matrixB[1][1])
    q = (matrixA[1][0] + matrixA[1][1]) * matrixB[0][0]
    r = matrixA[0][0] * (matrixB[0][1] - matrixB[1][1])
    s = matrixA[1][1] * (matrixB[1][0] - matrixB[0][0])
    t = (matrixA[0][0] + matrixA[0][1]) * matrixB[1][1]
    u = (matrixA[1][0] - matrixA[0][0]) * (matrixB[0][0] + matrixB[0][1])
    v = (matrixA[0][1] - matrixA[1][1]) * (matrixB[1][0] + matrixB[1][1])
    return [[p+s-t+v, r+t], [q+s, p+r-q+u]]

""" Version 1 (no numpy) """

def msub(matrixA, matrixB):
    c = []
    for i in range(len(matrixA)):
        cx = []
        for j in range(len(matrixA[i])):
            cx.append(matrixA[i][j] - matrixB[i][j])
        c.append(cx)
    return c

def madd(matrixA, matrixB):
    c = []
    for i in range(len(matrixA)):
        cx = []
        for j in range(len(matrixA[i])):
            cx.append(matrixA[i][j] + matrixB[i][j])
        c.append(cx)
    return c

def split_array(matrix):
    m11 = []
    m12 = []
    m21 = []
    m22 = []
    for i in range(len(matrix) // 2):
        m11.append(matrix[i][:len(matrix) // 2])
        m12.append(matrix[i][len(matrix) // 2:])
    for i in range(len(matrix) // 2, len(matrix)):
        m21.append(matrix[i][:len(matrix) // 2])
        m22.append(matrix[i][len(matrix) // 2:])
    return [m11, m12, m21, m22]

def multi(matrixA, matrixB):
    if len(matrixA) == 2:
        return brute(matrixA, matrixB)
    else:
        subA = split_array(matrixA)
        subB = split_array(matrixB)
        c11 = madd(multi(subA[0], subB[0]), multi(subA[1], subB[2]))
        c12 = madd(multi(subA[0], subB[1]), multi(subA[1], subB[3]))
        c21 = madd(multi(subA[2], subB[0]), multi(subA[3], subB[2]))
        c22 = madd(multi(subA[2], subB[1]), multi(subA[3], subB[3]))
        return [c11[i] + c12[i] for i in range(len(c11))] + [c21[i] + c22[i] for i in range(len(c21))]

def ready_to_multiply(fileA, fileB):
    matrixA = read_file(fileA)
    matrixB = read_file(fileB)
    new_dim = max(2**math.ceil(math.log2(len(matrixA))), 1)
    n_matrixA = [[0]*new_dim for _ in range(new_dim)]
    n_matrixB = [[0]*new_dim for _ in range(new_dim)]
    for i in range(len(matrixA)):
        for j in range(len(matrixA)):
            n_matrixA[i][j] = matrixA[i][j]
            n_matrixB[i][j] = matrixB[i][j]
    return n_matrixA, n_matrixB

""" Version 2 (using numpy) """

def split_array_np(matrix):
    m = len(matrix) // 2
    return [matrix[:m, :m], matrix[:m, m:], matrix[m:, :m], matrix[m:, m:]]

def madd_np(matrixA, matrixB):
    return np.add(matrixA, matrixB)

def msub_np(matrixA, matrixB):
    return np.subtract(matrixA, matrixB)

def multi_np(matrixA, matrixB):
    if len(matrixA) == 2:
        return brute(matrixA, matrixB)
    else:
        subA = split_array_np(matrixA)
        subB = split_array_np(matrixB)
        c11 = madd_np(multi_np(subA[0], subB[0]), multi_np(subA[1], subB[2]))
        c12 = madd_np(multi_np(subA[0], subB[1]), multi_np(subA[1], subB[3]))
        c21 = madd_np(multi_np(subA[2], subB[0]), multi_np(subA[3], subB[2]))
        c22 = madd_np(multi_np(subA[2], subB[1]), multi_np(subA[3], subB[3]))
        return [c11[i] + c12[i] for i in range(len(c11))] + [c21[i] + c22[i] for i in range(len(c21))]

def ready_to_multiply_np(fileA, fileB):
    matrixA = read_file(fileA)
    matrixB = read_file(fileB)
    new_dim = max(2**math.ceil(math.log2(len(matrixA))), 1)
    n_matrixA = [[0]*new_dim for _ in range(new_dim)]
    n_matrixB = [[0]*new_dim for _ in range(new_dim)]
    for i in range(len(matrixA)):
        for j in range(len(matrixA)):
            n_matrixA[i][j] = matrixA[i][j]
            n_matrixB[i][j] = matrixB[i][j]
    return np.array(n_matrixA), np.array(n_matrixB)

def results(fileA, fileB):
    start = time.time()
    r = total(multi(*ready_to_multiply(fileA, fileB)))
    print(f'File {fileA} on took {time.time() - start} seconds: {r}')
    np_start = time.time()
    np_r = total(multi_np(*ready_to_multiply_np(fileA, fileB)))
    print(f'File {fileA} on took {time.time() - np_start} seconds with np: {np_r}')

results('1a-1.txt', '1b-1.txt')
results('3a.txt', '3b.txt')
results('4a.txt', '4b.txt')
results('5a.txt', '5b.txt')
results('6a-1.txt', '6b-1.txt')
results('8a.txt', '8b.txt')



"""
p = multi(madd(subA[0], subA[3]), madd(subB[0], subB[3]))
q = multi(madd(subA[2], subA[3]), subB[0])
r = multi(subA[0], msub(subB[1], subB[3]))
s = multi(subA[3], msub(subB[2], subB[0]))
t = multi(madd(subA[0], subA[1]), subB[3])
u = multi(msub(subA[2], subA[0]), madd(subB[0], subB[1]))
v = multi(msub(subA[1], subA[3]), madd(subB[2], subB[3]))
c11 = madd(msub(madd(p, s), t), v)  # p+s-t+v
c12 = madd(r, t)  # r+t
c21 = madd(q, s)  # q+s
c22 = madd(msub(madd(p, r), q), u)  # r+r-q+u
"""