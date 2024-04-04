import numpy as np


def run_strassen(matrix_a, matrix_b):
    if len(matrix_a) <= 64:
        n = len(matrix_a)
        result = [[0 for _ in range(n)] for _ in range(n)]
        for i in range(n):
            for j in range(n):
                for k in range(n):
                    result[i][j] += matrix_a[i][k] * matrix_b[k][j]
        return result
    a11 = []
    a12 = []
    a21 = []
    a22 = []
    b11 = []
    b12 = []
    b21 = []
    b22 = []
    half = len(matrix_a) // 2
    for i in range(half):
        a11.append(matrix_a[i][:half])
        a12.append(matrix_a[i][half:])
        a21.append(matrix_a[i + half][:half])
        a22.append(matrix_a[i + half][half:])
        b11.append(matrix_b[i][:half])
        b12.append(matrix_b[i][half:])
        b21.append(matrix_b[i + half][:half])
        b22.append(matrix_b[i + half][half:])
    p1 = run_strassen(a11, merge_matrix(b12, b22, -1))
    p2 = run_strassen(merge_matrix(a11, a12), b22)
    p3 = run_strassen(merge_matrix(a21, a22), b11)
    p4 = run_strassen(a22, merge_matrix(b21, b11, -1))
    p5 = run_strassen(merge_matrix(a11, a22), merge_matrix(b11, b22))
    p6 = run_strassen(merge_matrix(a12, a22, -1), merge_matrix(b21, b22))
    p7 = run_strassen(merge_matrix(a11, a21, -1), merge_matrix(b11, b12))
    c11 = merge_matrix(merge_matrix(merge_matrix(p5, p4), p2, -1), p6)
    c12 = merge_matrix(p1, p2)
    c21 = merge_matrix(p3, p4)
    c22 = merge_matrix(merge_matrix(merge_matrix(p1, p5), p3, -1), p7, -1)
    return [c11[i] + c12[i] for i in range(len(c11))] + [c21[i] + c22[i] for i in range(len(c21))]


def strassen(file_a_path, file_b_path):
    matrix_a = [[int(i) for i in a.split(', ')] for a in open(file_a_path).read()[2:-2].split('}, {')]
    matrix_b = [[int(i) for i in a.split(', ')] for a in open(file_b_path).read()[2:-2].split('}, {')]
    padding = int(2 ** np.ceil(np.log2(len(matrix_a))) - len(matrix_a))
    pad_matrix(matrix_a, padding)
    pad_matrix(matrix_b, padding)
    return sum([sum(row) for row in run_strassen(matrix_a, matrix_b)])


def numpy_dot(file_a_path, file_b_path):
    matrix_a = np.array([[int(i) for i in a.split(', ')] for a in open(file_a_path).read()[2:-2].split('}, {')])
    matrix_b = np.array([[int(i) for i in a.split(', ')] for a in open(file_b_path).read()[2:-2].split('}, {')])
    return np.sum(np.dot(matrix_a, matrix_b))


def merge_matrix(matrix_a, matrix_b, multiplier=1):
    result = []
    n = len(matrix_a)
    for i in range(n):
        row = []
        for j in range(n):
            row.append(matrix_a[i][j] + (matrix_b[i][j] * multiplier))
        result.append(row)
    return result


def pad_matrix(matrix, padding_size):
    for i in range(len(matrix)):
        matrix[i] += [0 for _ in range(padding_size)]
    for i in range(padding_size):
        matrix.append([0 for _ in range(padding_size + len(matrix))])


def split_and_solve(matrix_a, matrix_b):
    if len(matrix_a) <= 64:
        n = len(matrix_a)
        result = [[0 for _ in range(n)] for _ in range(n)]
        for i in range(n):
            for j in range(n):
                for k in range(n):
                    result[i][j] += matrix_a[i][k] * matrix_b[k][j]
        return result
    a11 = []
    a12 = []
    a21 = []
    a22 = []
    b11 = []
    b12 = []
    b21 = []
    b22 = []
    half = len(matrix_a) // 2
    for i in range(half):
        a11.append(matrix_a[i][:half])
        a12.append(matrix_a[i][half:])
        a21.append(matrix_a[i + half][:half])
        a22.append(matrix_a[i + half][half:])
        b11.append(matrix_b[i][:half])
        b12.append(matrix_b[i][half:])
        b21.append(matrix_b[i + half][:half])
        b22.append(matrix_b[i + half][half:])
    c11 = merge_matrix(split_and_solve(a11, b11), split_and_solve(a12, b21))
    c12 = merge_matrix(split_and_solve(a11, b12), split_and_solve(a12, b22))
    c21 = merge_matrix(split_and_solve(a21, b11), split_and_solve(a22, b21))
    c22 = merge_matrix(split_and_solve(a21, b12), split_and_solve(a22, b22))
    return [c11[i] + c12[i] for i in range(len(c11))] + [c21[i] + c22[i] for i in range(len(c21))]


def divide_and_conquer(file_a_path, file_b_path):
    matrix_a = [[int(i) for i in a.split(', ')] for a in open(file_a_path).read()[2:-2].split('}, {')]
    matrix_b = [[int(i) for i in a.split(', ')] for a in open(file_b_path).read()[2:-2].split('}, {')]
    padding = int(2 ** np.ceil(np.log2(len(matrix_a))) - len(matrix_a))
    pad_matrix(matrix_a, padding)
    pad_matrix(matrix_b, padding)
    return sum([sum(row) for row in split_and_solve(matrix_a, matrix_b)])


def brute_force(file_a_path, file_b_path):
    matrix_a = [[int(i) for i in a.split(', ')] for a in open(file_a_path).read()[2:-2].split('}, {')]
    matrix_b = [[int(i) for i in a.split(', ')] for a in open(file_b_path).read()[2:-2].split('}, {')]
    n = len(matrix_a)
    result = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            for k in range(n):
                result[i][j] += matrix_a[i][k] * matrix_b[k][j]
    return sum([sum(row) for row in result])
