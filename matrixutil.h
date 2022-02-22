//
// Created by yoonsikjung on 2022/02/20.
//
//
// Created by yoonsikjung on 2022/02/20.
//

#ifndef SOLVER_MATRIXUTIL_H
#define SOLVER_MATRIXUTIL_H

#endif //SOLVER_MATRIXUTIL_H

#include <vector>
#include <iostream>

static std::vector<float> vecAdd(std::vector<float> vec1, std::vector<float> vec2) {
    if (vec1.size() != vec2.size())
        std::cout << "wrong size" << std::endl;
    std::vector<float> res;
    int len = vec1.size();
    for (int i = 0; i < len; i++) {
        res.push_back(vec1[i] + vec2[i]);
    }
    return res;
}

static std::vector<float> vecMul(std::vector<float> vec1, float num) {
    std::vector<float> res;
    for (int i = 0; i < vec1.size(); i++)
        res.push_back(vec1[i] * num);
    return res;
}

static std::vector<std::vector<float>> inverseMatrix(const std::vector<std::vector<float>> mat) {
    // gause-jordan elimination
    int ncol = mat[0].size();
    int nrow = mat.size();

    // calc determinant

    // set matrix
    std::vector<std::vector<float>> inv;
    inv.resize(nrow, std::vector<float>(2 * ncol, 0));

    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            inv[i][j] = mat[i][j];
        }
        for (int j = 0; j < ncol; j++) {
            inv[i][ncol + i] = 1;
        }
    }

    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < nrow; j++) {
            if (i == j)
                continue;
            if (inv[i][i] == 0)
                continue;
            float divider = -1 * inv[j][i] / inv[i][i];
            inv[j] = vecAdd(vecMul(inv[i], divider), inv[j]);
//                break;
        }
        inv[i] = vecMul(inv[i], 1 / inv[i][i]);
    }

    std::vector<std::vector<float>> res;
    res.resize(nrow, std::vector<float>(ncol, 0));

    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            res[i][j] = inv[i][j + ncol];
        }
    }
    return res;

}


template <typename T>
static void printVec(std::vector<T> vec1) {
    std::cout << std::endl;
    for (auto i: vec1)
        std::cout << i << " ";
    std::cout << std::endl;
}
template <typename T>
static void printMat(std::vector<std::vector<T>> mat) {
    std::cout << std::endl;
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


static float vecSumProduct(std::vector<float> vec1, std::vector<float> vec2) {
    if (vec1.size() != vec2.size())
        throw "invaild vector size";

    float res;

    for (int i = 0; i < vec1.size(); i++) {
        res += vec1[i] * vec2[i];
    }

    return res;
}


static std::vector<std::vector<float>>
matMul(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2) {

    if (mat1[0].size() != mat2.size()) {
        throw "invalid matrix size";
    }
    int resRow = mat1.size();
    int resCol = mat2[0].size();

    std::vector<std::vector<float>> res;
    res.resize(resRow, std::vector<float>(resCol));

    for (int i = 0; i < mat1.size(); i++) {
        for (int j = 0; j < mat2[0].size(); j++) {
            std::vector<float> vec1, vec2;
            vec1 = mat1[i];
            for (int k = 0; k < mat2.size(); k++) {
                vec2.push_back(mat2[k][j]);
            }
            res[i][j] = vecSumProduct(vec1, vec2);
        }
    }
    return res;
}

static std::vector<float> matMul(std::vector<std::vector<float>> mat1, std::vector<float> vec) {
    if (mat1[0].size() != vec.size()) {
        throw "invalid matrix/vector size";
    }
    int resRow = mat1.size();
    int resCol = vec.size();

    std::vector<float> res;

    for (int i = 0; i < mat1.size(); i++) {
        res.push_back(vecSumProduct(mat1[i], vec));
    }
    return res;
}

static std::vector<float> matVecMul(std::vector<std::vector<float>> mat1, std::vector<float> vec) {
    if (mat1[0].size() != vec.size()) {
        throw "invalid matrix/vector size";
    }
    int resRow = mat1.size();
    int resCol = vec.size();

    std::vector<float> res;

    for (int i = 0; i < mat1.size(); i++) {
        res.push_back(vecSumProduct(mat1[i], vec));
    }
    return res;
}
