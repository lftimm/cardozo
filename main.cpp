#include <iostream>
#include "algos.h"
#include "vector.h"

int main() {
    cardozo::Transform<4,4> a{{
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    }};

    cardozo::Vector v{4};
    v(0) = 1;
    v(1) = 2;
    v(2) = 1.3;
    v(3) = 1;
    
    cardozo::Vector x{4};
    x(0) = 0;
    x(1) = 0;
    x(2) = 0;
    x(3) = 0;

    std::cout << cardozo::linear_solve_CG(x,a,v)<< "\n";
}
