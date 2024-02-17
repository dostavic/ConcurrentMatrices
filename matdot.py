import numpy as np


def read_matrix(file_path):
    with open(file_path, 'r') as file:
        rows, cols = map(int, file.readline().split())
        matrix = np.array([list(map(int, line.split())) for line in file], dtype=int)

        return matrix


def dot_matrix(matrix1, matrix2):
    res = np.dot(matrix1, matrix2)
    np.savetxt("mat_res_p.txt", res, fmt='%d')


matrix1 = read_matrix("mat7.txt")
matrix2 = read_matrix("mat8.txt")

dot_matrix(matrix1, matrix2)
