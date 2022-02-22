#include <iostream>
#include <vector>
#include <array>
#include "matrixutil.h"
#include <algorithm>
#include "lp.h"
//#include <armadillo>
//#include "/usr/local/include/armadillo"


int main(){
//    MatrixUtil mu;
//    std::vector<std::vector<float>> inv;
//
//    inv.push_back({2,-1,0});
//    inv.push_back({1,0,-1});
//    inv.push_back({1,0,1});

//    std::vector<float> c = {-6, -5, -4, 0, 0, 0};
//    std::vector<float> b = {240, 360, 300};
//    std::vector<std::vector<float>> a;
//    a.push_back({2,1,3,1,0,0});
//    a.push_back({1,3,2,0,1,0});
//    a.push_back({2,1,2,0,0,1});

    std::vector<float> c = {3, 4, 5, 0, 0, 0};
    std::vector<float> b = {-5,-6};
    std::vector<std::vector<float>> a;
    a.push_back({-1,-2,-3,1,0});
    a.push_back({-2,-2,-1,0,1});


    LPModel model{a, b, c, std::vector<float>(5,0)};
    model.doSimplex();
    printVec(model.X);
    printVec(model.basisIdx);
    printVec(model.nonbasisIdx);

    std::cout<<model.niter;

//    printMat(model.A);
//    printMat(model.BasisInv);
//    printVec(model.reducedCost);
//    int ent = model.selectEnteringVariable();
//    std::cout << "entering:" << ent;



}