#pragma once
#include <stdexcept>

#include "vector.h"
#include "matrix.h"

namespace cardozo::algos 
{
    template<typename S>
    Vector congruentGradient(Vector x, Matrix<S>& A, Vector& B, float eps) {

        const int max_iteration_limit{2*A.getRows()};
        Vector res = multiply(A,x) - B;
        Vector delta = res * -1;
    
        for(int i = 0; i < max_iteration_limit; i++)
        {
            if (magnitude(res) <= eps)
                return x;
    
            Vector D = multiply(A,delta);
            float beta = dot(res,delta) * (-1/dot(delta,D));
            x += delta * beta;
            
    
            res = multiply(A,x) - B;
            float chi = dot(res,D) * (1/dot(delta,D));
            delta = delta*chi - res;
        }
    
        throw std::runtime_error("Could not converge solver");
    }
}
