import time

import numpy as np


def read_matrix(file_path):
    with open(file_path, 'r') as file:
        rows, cols = map(int, file.readline().split())
        matrix = np.array([list(map(int, line.split())) for line in file], dtype=int)

        return matrix


def dot_matrix(matrix1, matrix2):
    return np.dot(matrix1, matrix2)


matrix1 = read_matrix("mat500x500_1.txt")
matrix2 = read_matrix("mat500x500_2.txt")
matrix3 = []
start = time.time()

matrix3 = dot_matrix(matrix1, matrix2)

end = time.time()

print(f"Час виконання Пітон: {end - start} секунд.")

np.savetxt("mat_res_p.txt", matrix3, fmt='%.2f')
