import time
import numpy as np


def brute_force(matrix_a, matrix_b):
    result = np.array([[0 for _ in range(len(matrix_a))] for _ in range(len(matrix_a))])
    n = len(matrix_a)
    for i in range(n):
        for j in range(n):
            for k in range(n):
                result[i][j] += matrix_a[i][k] * matrix_b[k][j]
    return result


def divide_and_conquer(matrix_a, matrix_b):
    assert len(matrix_a) == len(matrix_b)
    if len(matrix_a) <= 64:
        return brute_force(matrix_a, matrix_b)

    a_row, a_col = matrix_a.shape
    a11 = matrix_a[:a_row // 2, :a_col // 2]
    a12 = matrix_a[:a_row // 2, a_col // 2:]
    a21 = matrix_a[a_row // 2:, :a_col // 2]
    a22 = matrix_a[a_row // 2:, a_col // 2:]
    b_row, b_col = matrix_b.shape
    b11 = matrix_b[:b_row // 2, :b_col // 2]
    b12 = matrix_b[:b_row // 2, b_col // 2:]
    b21 = matrix_b[b_row // 2:, :b_col // 2]
    b22 = matrix_b[b_row // 2:, b_col // 2:]

    c11 = divide_and_conquer(a11, b11) + divide_and_conquer(a12, b21)
    c12 = divide_and_conquer(a11, b12) + divide_and_conquer(a12, b22)
    c21 = divide_and_conquer(a21, b11) + divide_and_conquer(a22, b21)
    c22 = divide_and_conquer(a21, b12) + divide_and_conquer(a22, b22)

    return np.array([c11[i] + c12[i] for i in range(len(c11))] + [c21[i] + c22[i] for i in range(len(c21))])


def strassen(matrix_a, matrix_b):
    if len(matrix_a) <= 8:
        return brute_force(matrix_a, matrix_b)

    a_row, a_col = matrix_a.shape
    a11 = matrix_a[:a_row // 2, :a_col // 2]
    a12 = matrix_a[:a_row // 2, a_col // 2:]
    a21 = matrix_a[a_row // 2:, :a_col // 2]
    a22 = matrix_a[a_row // 2:, a_col // 2:]
    b_row, b_col = matrix_b.shape
    b11 = matrix_b[:b_row // 2, :b_col // 2]
    b12 = matrix_b[:b_row // 2, b_col // 2:]
    b21 = matrix_b[b_row // 2:, :b_col // 2]
    b22 = matrix_b[b_row // 2:, b_col // 2:]

    p1 = strassen(a11, b12 - b22)
    p2 = strassen(a11 + a12, b22)
    p3 = strassen(a21 + a22, b11)
    p4 = strassen(a22, b21 - b11)
    p5 = strassen(a11 + a22, b11 + b22)
    p6 = strassen(a12 - a22, b21 + b22)
    p7 = strassen(a11 - a21, b11 + b12)
    c11 = p5 + p4 - p2 + p6
    c12 = p1 + p2
    c21 = p3 + p4
    c22 = p1 + p5 - p3 - p7

    return np.array([c11[i] + c12[i] for i in range(len(c11))] + [c21[i] + c22[i] for i in range(len(c21))])


def solve(file_a, file_b):
    matrix_a = np.array([[int(i) for i in a.split(', ')] for a in open(file_a).read()[2:-2].split('}, {')])
    matrix_b = np.array([[int(i) for i in a.split(', ')] for a in open(file_b).read()[2:-2].split('}, {')])
    
    padding = int(2 ** np.ceil(np.log2(len(matrix_a))) - len(matrix_a))
    matrix_a = np.pad(matrix_a, pad_width=((0, padding), (0, padding)), constant_values=0)
    matrix_b = np.pad(matrix_b, pad_width=((0, padding), (0, padding)), constant_values=0)

    # start = time.time()
    # ans = np.sum(np.dot(matrix_a, matrix_b))  # fastest, numpy voodoo magic
    # print(f'dot. {round(ans, 3)} | took {round(time.time() - start, 4)} seconds.')
    # start = time.time()
    # ans = np.sum(matrix_a @ matrix_b)  # pretty fast, using built-in python functions
    # print(f'@. {round(ans, 3)} | took {round(time.time() - start, 4)} seconds.')
    start = time.time()
    ans = np.sum(strassen(matrix_a, matrix_b))  # far from the first two, but faster due to 7 vs 8 multiplications
    # print(f'strassen. {round(ans, 3)} | took {round(time.time() - start, 4)} seconds.')
    # start = time.time()
    # ans = np.sum(divide_and_conquer(matrix_a, matrix_b))  # can be close to strassen, can be worse than monkey
    # print(f'dac. {round(ans, 3)} | took {round(time.time() - start, 4)} seconds.')
    # start = time.time()
    # ans = np.sum(brute_force(matrix_a, matrix_b))  # monkey method go brrr
    # print(f'monkey. {round(ans, 3)} | took {round(time.time() - start, 4)} seconds.')
    end_time = time.time() - start
    return ans, end_time


if __name__ == '__main__':
    for file_num in [1, 3, 4, 5, 6, 8]:  # range(11):
        sol, t = solve(f'./Strassen Algorithm/{file_num}a.txt', f'./Strassen Algorithm/{file_num}b.txt')
        print(f'{file_num}. {round(sol, 3)} | took {round(t, 4)} seconds.')
