#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <iomanip>

void saveMat(std::vector<std::vector<float>>& mat, const std::string& filepath) {
    std::ofstream result_file(filepath);

    for (const auto& row : mat) {
        for (const auto& element : row) {
            result_file << std::fixed << std::setprecision(2) << element << " ";
        }
        result_file << "\n";
    }

    result_file.close();
}

void multiplyPart(const std::vector<std::vector<float>>& mat1, const std::vector<std::vector<float>>& mat2,
                  std::vector<std::vector<float>>& mat3, int from, int to) {
    for (int i = from; i < to; i++) {
        for (int j = 0; j < mat2[0].size(); j++) {
            for (int k = 0; k < mat1.size(); k++) {
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void parallelMatrixMultiply(const std::vector<std::vector<float>>& mat1, const std::vector<std::vector<float>>& mat2,
                            std::vector<std::vector<float>>& mat3) {
    int numThreads = 16;
    int n = mat1.size();
    std::vector<std::thread> threads(numThreads);

    for (int i = 0; i < numThreads; i++) {
        int from = i * n / numThreads;
        int to = (i + 1) * n / numThreads;
        threads[i] = std::thread(multiplyPart, cref(mat1), cref(mat2), ref(mat3), from, to);
    }

    for (auto& t : threads) {
        t.join();
    }
}

std::vector<std::vector<float>> createMat(std::vector<std::vector<float>>& mat1, std::vector<std::vector<float>>& mat2) {
    std::vector<std::vector<float>> mat3(mat1.size(), std::vector<float>(mat2[0].size(), 0));

    return mat3;
}

std::vector<std::vector<float>> readMat(const std::string& filepath) {
    std::ifstream fp(filepath);

    if (!fp) {
        return {};
    }

    int r, c;
    fp >> r >> c;
    std::vector<std::vector<float>> mat(r, std::vector<float>(c));

    for (int row = 0; row < r; row++) {
        for (int column = 0; column < c; column++) {
            fp >> mat[row][column];
        }
    }

    return mat;
}

int main() {
    std::vector<std::vector<float>> mat1txt = readMat("mat500x500_1.txt");
    std::vector<std::vector<float>> mat2txt = readMat("mat500x500_2.txt");

    if (mat1txt.size() != mat2txt[0].size()) {
        return EXIT_FAILURE;
    }

    std::vector<std::vector<float>> mat3 = createMat(mat1txt, mat2txt);
    auto start = std::chrono::high_resolution_clock::now();

    parallelMatrixMultiply(mat1txt, mat2txt, mat3);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Час виконання паралельного: " << elapsed.count() << " секунд.\n";

    saveMat(mat3, "mat_res_c_p.txt");

    return 0;
}
