//
// Created by yoonsikjung on 2021/12/17.
//
#include <vector>
#include "lp.h"
#include "matrixutil.h"


// implementations
LPModel::LPModel(std::vector<std::vector<float>> a, std::vector<float> b, std::vector<float> c, std::vector<float> x) {

    nrow = a.size();
    ncol = a[0].size();
    if(nrow > ncol)
        throw "invaild matrix size";

    X.resize(ncol, 0);
    // resize(sz, x) : sz로 크기를 조정하고 x로 초기화한다.
    A.resize(nrow, std::vector<float>(ncol, 0));
    B.resize(nrow, 0);
    C.resize(ncol, 0);
//    reducedCost.resize(ncol, 0);

    for(int i = 0; i < ncol; i++)
        X[i] = x[i];

    for(int i = 0; i < nrow; i++){
        for(int j = 0; j < ncol; j++){
            A[i][j] = a[i][j];
        }
    }

    for(int i = 0; i < nrow; i++)
        B[i] = b[i];

    for(int i = 0; i < ncol; i++)
        C[i] = c[i];

    for(int i = 0; i < ncol; i++){
        if(i < nrow)
            basisIdx.push_back(i);
        else
            nonbasisIdx.push_back(i);
    }
    // resize를 해주어야 메모리를 확보함. 이 작업을 수행하지 않으면 값이 들어가지 못함
    Basis.resize(nrow, std::vector<float>(basisIdx.size(), 0));
    NonBasis.resize(nrow, std::vector<float>(nonbasisIdx.size(), 0));
    BasisInv.resize(nrow, std::vector<float>(basisIdx.size(), 0));

    // update x
    updateBasis();
    updateDecisionVariable();

//    updateReducedCost();

}
int LPModel::selectEnteringVariable(){

    std::vector<float> costBasis, costNonBasis;

    for(auto cb: basisIdx){
        costBasis.push_back(C[cb]);
    }
    for(auto cn: nonbasisIdx){
        costNonBasis.push_back(C[cn]);
    }

    for(auto nb : nonbasisIdx){
        std::vector<float> a;
        for(int i = 0; i < nrow; i++)
            a.push_back(A[i][nb]);

        auto t = matVecMul(BasisInv, a);
        auto rc = C[nb] - vecSumProduct(t, costBasis); // rc:reduced cost

        if(rc < 0){
//            std::cout <<"reducedCost: " <<rc <<std::endl;
            return nb;
        }

    }
    isOptimal = true;
    return NULL; // this case, there is no entering (enhancable variable)
}

//void LPModel::updateReducedCost(){
//
//    std::vector<float> costBasis, costNonBasis;
//
//    for(auto cb: basisIdx){
//        costBasis.push_back(C[cb]);
//    }
//    for(auto cn: nonbasisIdx){
//        costNonBasis.push_back(C[cn]);
//    }
//
//    // cost for non-basis : C_N - C_B B^-1 N
//    auto temp = matMul(BasisInv, NonBasis);
//    int tempIdx = 0;
//    for(auto n:nonbasisIdx){
//        std::vector<float> col;
//        for(int i = 0; i < temp.size(); i++){
//            col.push_back(temp[i][tempIdx]);
//        }
//        reducedCost[n] = vecSumProduct(costBasis, col);
//        tempIdx++;
//    }
////    printVec(reducedCost);
//}

void LPModel::updateBasis(){
    int temp_idx = 0;
    for(auto b:basisIdx){
        for(int i = 0; i < nrow; i++){
            Basis[i][temp_idx] = A[i][b];
        }
        temp_idx++;
    }

    temp_idx = 0;
    for(auto b:nonbasisIdx){
        for(int i = 0; i < nrow; i++){
            NonBasis[i][temp_idx] = A[i][b];
        }
        temp_idx++;
    }

    BasisInv = inverseMatrix(Basis);
}

void LPModel::updateDecisionVariable(){
    int tempIdx = 0;
    for(auto b:basisIdx){
        X[b] = vecSumProduct(BasisInv[tempIdx], B);
        tempIdx++;
    }
    tempIdx = 0;
    for(auto nb: nonbasisIdx){
        X[nb] = 0;
        tempIdx++;
    }
}

bool LPModel::checkFeasibility() {
    for(int j = 0; j < ncol; j++){
        if(X[j] < 0){
            isFeasible = false;
            return false;
        }

    }
    for(int i = 0; i < nrow; i++){
        float lhs = 0;
        for(int j = 0; j < ncol; j++){
            lhs += A[i][j] * X[j];
        }
        if(lhs > B[i]){
            isFeasible = false;
            return false;
        }
    }
    isFeasible = true;
    return true;
}

int LPModel::selectExitVariable(int enteringVariable) {
    std::vector<float> a;
    for(int i = 0; i < nrow; i++)
        a.push_back(A[i][enteringVariable]);

    auto temp = matVecMul(BasisInv, a);

    float minValue = 9999999;
    float minIdx = NULL;

    int tempIdx = 0;
    for(auto b : basisIdx){
        auto val = X[b] / temp[tempIdx];
        if(val < minValue){
            minValue = val;
            minIdx = b;
        }
        tempIdx++;
    }

    return minIdx;
}

bool LPModel::iterateSimplex(){
    // check optimality
//    if(checkOptimality())
//        return true;
//    // check feasibility (can skip?)
//    if(checkFeasibility()){
//        // nothing to do
//    }
//    else{
//        // 2-phase method?
//    }

    // find entering variable
    int enteringIdx = selectEnteringVariable();

    if(isOptimal & enteringIdx == NULL){
        std::cout <<"OPTIMAL" <<std::endl;
        return true;
    }

    // find exit variable using entering variable
    int exitIdx = selectExitVariable(enteringIdx);

    // update coefficients and variables
    std::replace(nonbasisIdx.begin(), nonbasisIdx.end(), enteringIdx, exitIdx);
    std::replace(basisIdx.begin(), basisIdx.end(), exitIdx, enteringIdx);

    updateBasis();
    updateDecisionVariable();

    return isOptimal;
}

int LPModel::doSimplex(){
    while(!isOptimal){
        iterateSimplex();
        niter++;
    }
};


// wrapper에서 inequality로 인한 slack/artificial variable까지 처리해서 생성자에 입력함
// header에서 LPModel 불러오려면 어떻게? -> 처리하면 header로 보내기
class ModelWrapper{
public:
    LPModel createModel();
};
