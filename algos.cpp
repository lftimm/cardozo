#include <sstream>
#include "algos.h"

namespace cardozo 
{
    Vector multiply(const Matrix& a, const Vector& b) {
        int cols = a.getCols();
        int rows = a.getRows();
        int len = b.getSize();
    
        if (cols != len)
        {
            std::stringstream ss{};
            ss << "multiply: matrix and vector are incompatible\n"
               << "M shape: (" << a.getRows() << ", " << a.getCols() << ")\n"
               << "V len: (" << b.getSize() << ")\n"
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
    
    
    Vector linear_solve_CG(Vector x, Matrix& A, Vector& B, float eps) {

        Vector res = multiply(A,x) - B;
        Vector delta = res * -1;
    
        while (true) 
        {
            if (res.length() <= eps) {
                return x;
            }
    
            Vector D = multiply(A,delta);
            float beta = res.dot(delta) * (-1/delta.dot(D));
            x += delta * beta;
            
    
            res = multiply(A,x) - B;
            float chi = res.dot(D) * (1/delta.dot(D));
            delta = delta*chi - res;
        }
    }
}
