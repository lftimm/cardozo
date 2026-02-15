#pragma once

#include "matrix.h"
#include "vector.h"
#include "dense_cr.h"

namespace cardozo::algos
{
    Matrix<DenseCR> transpose(const Matrix<DenseCR>& m);

    template<typename S>
    Vector conjugateGradient(Vector x, const Matrix<S>& A, const Vector& B, float eps=1e-5) {

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

    template<typename S>
    Matrix<S> multiply(const Matrix<S>& A, const Matrix<S>& B) {
        
        assert(A.getCols() == B.getRows() && "Impossible to multiply");

        Matrix<DenseCR> ret{A.getRows(), B.getCols()};
        
        for(int i = 0; i < A.getRows(); i++)
        {
            for(int k = 0; k < A.getCols(); k++) 
            {
                double r = A(i,k); 
                for(int j = 0; j < B.getCols(); j++) 
                {
                    ret(i,j) += r * B(k,j); 
                }
            }
        }

        return ret;
    }


    std::pair<Matrix<DenseCR>,Matrix<DenseCR>> lu_decompose(const Matrix<DenseCR>& m);

    Matrix<DenseCR> cholesky_decompose(const Matrix<DenseCR>& m);
}

