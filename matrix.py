import numpy as np

arr = np.random.uniform(0.0, 100, [2000, 2000])

file_path = "mat2000x2000_2_f.txt"

with open(file_path, 'w') as file:
    file.write(f"{arr.shape[0]} {arr.shape[1]}\n")

    for row in arr:
        file.write(" ".join(map(str, row)) + "\n")
