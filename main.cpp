#include <iostream>
#include <fstream>
#include <vector>

void saveMat(std::vector<std::vector<int>>& mat, const std::string& filepath) {
    std::ofstream result_file(filepath);

    for (const auto& row : mat) {
        for (const auto& element : row) {
            result_file << element << " ";
        }
        result_file << "\n";
    }

    result_file.close();
}

void printMat(std::vector<std::vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> readMat(const std::string& filepath) {
    std::ifstream fp(filepath);

    if (!fp) {
        return {};
    }

    int r, c;
    fp >> r >> c;
    std::vector<std::vector<int>> mat(r, std::vector<int>(c));

    for (int row = 0; row < r; row++) {
        for (int column = 0; column < c; column++) {
            fp >> mat[row][column];
        }
    }

    return mat;
}

std::vector<std::vector<int>> mulMat(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>> mat2)
{
    std::vector<std::vector<int>> result(mat1.size(), std::vector<int>(mat2[0].size()));

    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat2[0].size(); j++) {
            result[i][j] = 0;

            for (int k = 0; k < mat2.size(); k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

int main()
{
    std::vector<std::vector<int>> mat1txt = readMat("../mat7.txt");
    std::vector<std::vector<int>> mat2txt = readMat("../mat8.txt");

    if (mat1txt.size() != mat2txt[0].size()) {
        return EXIT_FAILURE;
    }

    std::vector<std::vector<int>> resMat = mulMat(mat1txt, mat2txt);
    saveMat(resMat, "../mat_res_c.txt");

    return 0;
}
