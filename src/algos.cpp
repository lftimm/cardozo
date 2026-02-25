#include <iostream>
#include <cmath>
#include "matrix.h"
#include "vector.h"
#include "algos.h"

namespace cardozo::algos 
{
    Matrix<DenseCR> transpose(const Matrix<DenseCR>& m)
    {
        Matrix<DenseCR> ret{m.getRows(),m.getCols()};

        for(int i = 0; i < m.getRows(); i++)
        {
            for(int j = 0; j < m.getCols(); j++)
            {
                ret(i,j) = m(j,i);
            }
        }

        return ret;
    }


    std::pair<Matrix<DenseCR>,Matrix<DenseCR>> lu_decompose(const Matrix<DenseCR>& m) {

        Matrix<DenseCR> L{m.getRows(),m.getCols()};
        Matrix<DenseCR> U{m.getRows(),m.getCols()};

        int n = m.getRows();

        for (int i = 0; i < n; i++) 
        {
            for (int k = i; k < n; k++)
            {
                int sum = 0;
                for (int j = 0; j < i; j++)
                    sum += (L(i,j) * U(j,k));

                U(i,k) = m(i,k) - sum;
            }

            for (int k = i; k < n; k++) 
            {
                if (i == k)
                    L(i,i) = 1; 
                else 
                {
                    int sum = 0;
                    for (int j = 0; j < i; j++)
                        sum += (L(k,j) * U(j,i));

                    L(k,i) = (m(k,i) - sum) / U(i,i);
                }
            }
        }

        return std::pair<Matrix<DenseCR>,Matrix<DenseCR>>{L,U};
    }

    Matrix<DenseCR> cholesky_decompose(const Matrix<DenseCR>& A) 
    {
        int dimensionSize = A.getRows();

        Matrix<DenseCR> L{A.getRows(),A.getCols()};

        for (int j = 0; j < dimensionSize; j++) {
            double sum = 0;
            for (int k = 0; k < j; k++) {
                sum += L(j, k) * L(j, k);
            }
            L(j, j) = sqrt(A(j, j) - sum);
        
            for (int i = j + 1; i < dimensionSize; i++) {
                double off_diag_sum = 0;
                for (int k = 0; k < j; k++) {
                    off_diag_sum += L(i, k) * L(j, k);
                }
                L(i, j) = (1.0 / L(j, j) * (A(i, j) - off_diag_sum));
            }
        }

        return L;
    }
}
