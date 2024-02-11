import numpy as np


def run_strassen(matrix_a, matrix_b):
    if len(matrix_a) <= 64:
        return np.dot(matrix_a, matrix_b)

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

    p1 = run_strassen(a11, b12 - b22)
    p2 = run_strassen(a11 + a12, b22)
    p3 = run_strassen(a21 + a22, b11)
    p4 = run_strassen(a22, b21 - b11)
    p5 = run_strassen(a11 + a22, b11 + b22)
    p6 = run_strassen(a12 - a22, b21 + b22)
    p7 = run_strassen(a11 - a21, b11 + b12)
    c11 = p5 + p4 - p2 + p6
    c12 = p1 + p2
    c21 = p3 + p4
    c22 = p1 + p5 - p3 - p7

    return np.array([c11[i] + c12[i] for i in range(len(c11))] + [c21[i] + c22[i] for i in range(len(c21))])


def strassen(file_a_path, file_b_path):
    matrix_a = np.array([[int(i) for i in a.split(', ')] for a in open(file_a_path).read()[2:-2].split('}, {')])
    matrix_b = np.array([[int(i) for i in a.split(', ')] for a in open(file_b_path).read()[2:-2].split('}, {')])

    padding = int(2 ** np.ceil(np.log2(len(matrix_a))) - len(matrix_a))
    matrix_a = np.pad(matrix_a, pad_width=((0, padding), (0, padding)), constant_values=0)
    matrix_b = np.pad(matrix_b, pad_width=((0, padding), (0, padding)), constant_values=0)
    return np.sum(run_strassen(matrix_a, matrix_b))
