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
    # assert len(matrixA) == len(matrixB)
    # result = np.array([[0 for _ in range(len(matrixA))] for _ in range(len(matrixA))])
    # for i in range(len(matrixA)):
    #     for j in range(len(matrixB[0])):
    #         for k in range(len(matrixB)):
    #             result[i][j] += matrixA[i][k] * matrixB[k][j]
    # return result
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
    print(f'{fileA[21:-5]}. {round(r, 3)} | took {round(time.time() - start, 4)} seconds.')
    np_start = time.time()
    np_r = total(multi_np(*ready_to_multiply_np(fileA, fileB)))
    print(f'{fileA[21:-5]}. {round(r, 3)} | took {round(time.time() - np_start, 4)} seconds (np).')


# results('./Strassen Algorithm/1a.txt', './Strassen Algorithm/1b.txt')
# results('./Strassen Algorithm/3a.txt', './Strassen Algorithm/3b.txt')
# results('./Strassen Algorithm/4a.txt', './Strassen Algorithm/4b.txt')
# results('./Strassen Algorithm/5a.txt', './Strassen Algorithm/5b.txt')
# results('./Strassen Algorithm/6a.txt', './Strassen Algorithm/6b.txt')
# results('./Strassen Algorithm/8a.txt', './Strassen Algorithm/8b.txt')


def multiply_matrix(matrix_a, matrix_b):
    assert len(matrix_a) == len(matrix_b)
    if len(matrix_a) > 100:
        print(len(matrix_a))
    if len(matrix_a) <= 256:
        brute_force_result = np.array([[0 for _ in range(len(matrix_a))] for _ in range(len(matrix_a))])
        for i in range(len(matrix_a)):
            for j in range(len(matrix_b[0])):
                for k in range(len(matrix_b)):
                    brute_force_result[i][j] += matrix_a[i][k] * matrix_b[k][j]
        return brute_force_result
    a1, a2 = np.split(matrix_a, 2)
    b1, b2 = np.split(matrix_b, 2)
    a11, a12 = np.split(np.array(a1), 2, axis=1)
    a21, a22 = np.split(np.array(a2), 2, axis=1)
    b11, b12 = np.split(np.array(b1), 2, axis=1)
    b21, b22 = np.split(np.array(b2), 2, axis=1)

    c11 = multiply_matrix(a11, b11) + multiply_matrix(a12, b21)
    c12 = multiply_matrix(a11, b12) + multiply_matrix(a12, b22)
    c21 = multiply_matrix(a21, b11) + multiply_matrix(a22, b21)
    c22 = multiply_matrix(a21, b12) + multiply_matrix(a22, b22)
    return np.array([c11[i] + c12[i] for i in range(len(c11))] + [c21[i] + c22[i] for i in range(len(c21))])


def brute_force(matrix_a, matrix_b):
    assert len(matrix_a) == len(matrix_b)
    result = np.array([[0 for _ in range(len(matrix_a))] for _ in range(len(matrix_a))])
    for i in range(len(matrix_a)):
        for j in range(len(matrix_b[0])):
            for k in range(len(matrix_b)):
                result[i][j] += matrix_a[i][k] * matrix_b[k][j]
    return result


def solve(file_a, file_b, is_brute_force):
    matrix_a = np.array([[int(i) for i in a.split(', ')] for a in open(file_a).read()[2:-2].split('}, {')])
    matrix_b = np.array([[int(i) for i in a.split(', ')] for a in open(file_b).read()[2:-2].split('}, {')])
    # assert len(matrix_a) == len(matrix_b)
    # padding = int(2 ** np.ceil(np.log2(len(matrix_a))) - len(matrix_a))
    # matrix_a = np.pad(matrix_a, pad_width=((0, padding), (0, padding)), mode='constant', constant_values=0)
    # matrix_b = np.pad(matrix_b, pad_width=((0, padding), (0, padding)), mode='constant', constant_values=0)

    start = time.time()
    if is_brute_force:
        ans = np.sum(brute_force(matrix_a, matrix_b))
    else:
        # ans = np.sum(multiply_matrix(matrix_a, matrix_b))
        ans = np.sum(np.dot(matrix_a, matrix_b))
    end_time = time.time() - start
    return ans, end_time


if __name__ == '__main__':
    do_brute_force = False
    for file_num in [1, 3, 4, 5, 6, 8]:  # range(11):
        sol, t = solve(
            f'./Strassen Algorithm/{file_num}a.txt',
            f'./Strassen Algorithm/{file_num}b.txt',
            do_brute_force
        )
        print(f'{file_num}. {round(sol, 3)} | took {round(t, 4)} seconds.')

