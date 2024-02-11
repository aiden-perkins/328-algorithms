import numpy as np


def numpy_dot(file_a_path, file_b_path):
    matrix_a = np.array([[int(i) for i in a.split(', ')] for a in open(file_a_path).read()[2:-2].split('}, {')])
    matrix_b = np.array([[int(i) for i in a.split(', ')] for a in open(file_b_path).read()[2:-2].split('}, {')])
    return np.sum(np.dot(matrix_a, matrix_b))