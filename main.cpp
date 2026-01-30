#include <iostream>
#include "algos.h"
#include "matrix.h"
#include "sparse_cr.h"
#include "vector.h"

int main() {
    cardozo::Matrix<cardozo::SparseCR> a{{
        {1,0},
        {0,1}
    }};

    cardozo::Vector v{2};
    v(0) = 1;
    v(1) = 2;
    
    cardozo::Vector x{2};
    x(0) = 0;
    x(1) = 0;

    std::cout << cardozo::linear_solve_CG(x,a,v)<< "\n";
}
