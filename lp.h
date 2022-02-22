//
// Created by yoonsikjung on 2021/12/17.
//

#include <string>
#include <array>
#include <vector>

#ifndef SOLVER_LP_H
#define SOLVER_LP_H

#endif //SOLVER_LP_H




// suppose that model has standard form
class LPModel{
public:

public: // it'll be private
    int ncol;
    int nrow;
    int niter = 0;

    std::vector<std::vector<float>> A;
    std::vector<float> B;
    std::vector<float> C;
    std::vector<float> X;

    std::vector<int> basisIdx;
    std::vector<int> nonbasisIdx;

    std::vector<std::vector<float>> Basis, NonBasis, BasisInv;

    bool isOptimal = false;
    bool isFeasible = false;


public:
    LPModel(std::vector< std::vector<float >> a, std::vector<float> b, std::vector<float> c, std::vector<float> x);
    bool checkFeasibility();
    int selectEnteringVariable();
    int selectExitVariable(int enteringVariable);
    int doSimplex();
    bool iterateSimplex();
    void updateDecisionVariable();
    void updateBasis();
    void updateReducedCost();

};

