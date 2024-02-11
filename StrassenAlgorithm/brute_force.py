import numpy as np


def brute_force(file_a_path, file_b_path):
    matrix_a = np.array([[int(i) for i in a.split(', ')] for a in open(file_a_path).read()[2:-2].split('}, {')])
    matrix_b = np.array([[int(i) for i in a.split(', ')] for a in open(file_b_path).read()[2:-2].split('}, {')])
    padding = int(2 ** np.ceil(np.log2(len(matrix_a))) - len(matrix_a))
    matrix_a = np.pad(matrix_a, pad_width=((0, padding), (0, padding)), constant_values=0)
    matrix_b = np.pad(matrix_b, pad_width=((0, padding), (0, padding)), constant_values=0)
    result = np.array([[0 for _ in range(len(matrix_a))] for _ in range(len(matrix_a))])
    n = len(matrix_a)
    for i in range(n):
        for j in range(n):
            for k in range(n):
                result[i][j] += matrix_a[i][k] * matrix_b[k][j]
    return np.sum(result)
