#pragma once
#include <sstream>
#include "../headers/algos.h"

namespace cardozo::algos 
{
    template<typename S>
    Vector multiply(const Matrix<S>& a, const Vector& b) {
        int cols = a.getCols();
        int rows = a.getRows();
        int len = b.getLength();
    
        if (cols != len)
        {
            std::stringstream ss{};
            ss << "multiply: matrix and vector are incompatible\n"
               << "M shape: (" << a.getRows() << ", " << a.getCols() << ")\n"
               << "V len: (" << b.getLength() << ")\n"
               ;
    
            throw std::out_of_range(ss.str());
        }
    
        Vector res{rows};
        for (int i = 0 ; i < rows ; i++) {
            float acc = 0;
            for (int j = 0 ; j < cols ; j++) {
                acc += a(i,j) * b(j);
            }
            res(i) = acc;
        }
    
        return res;
    }
    
    
    template<typename S>
    Vector congruentGradient(Vector x, Matrix<S>& A, Vector& B, float eps) {

        Vector res = multiply(A,x) - B;
        Vector delta = res * -1;
    
        while (true) 
        {
            if (magnitude(res) <= eps) {
                return x;
            }
    
            Vector D = multiply(A,delta);
            float beta = dot(res,delta) * (-1/dot(delta,D));
            x += delta * beta;
            
    
            res = multiply(A,x) - B;
            float chi = dot(res,D) * (1/dot(delta,D));
            delta = delta*chi - res;
        }
    }
}
