import numpy as np


def numpy_dot(file_a, file_b):
    file_a_path = './StrassenAlgorithm/tests/' + file_a
    file_b_path = './StrassenAlgorithm/tests/' + file_b
    matrix_a = np.array([[int(i) for i in a.split(', ')] for a in open(file_a_path).read()[2:-2].split('}, {')])
    matrix_b = np.array([[int(i) for i in a.split(', ')] for a in open(file_b_path).read()[2:-2].split('}, {')])
    return np.sum(np.dot(matrix_a, matrix_b))
