import numpy as np

arr = np.random.randint(1, 100, [500, 500])
print(arr)

file_path = "mat8.txt"

with open(file_path, 'w') as file:
    file.write(f"{arr.shape[0]} {arr.shape[1]}\n")

    for row in arr:
        file.write(" ".join(map(str, row)) + "\n")
