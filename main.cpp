#include <iostream>
#include "algos.h"
#include "matrix.h"
#include "vector.h"

int main() {
    cardozo::Matrix a{2,2};
    a(0,0) = 4;
    a(0,1) = 1;
    a(1,0) = 1;
    a(1,1) = 3;

    cardozo::Vector v{2};
    v(0) = 1;
    v(1) = 2;
    
    cardozo::Vector x{2};
    x(0) = 0;
    x(1) = 0;

    std::cout << cardozo::linear_solve_CG(x,a,v)<< "\n";
}
