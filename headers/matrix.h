#pragma once
#include <initializer_list>
#include <sys/types.h>

#include "vector.h"
#include "dense_cr.h"
#include "stack_cr.h"
#include "sparse_cr.h"

namespace cardozo 
{
    template<typename Storage = DenseCR>
    class Matrix {
    private:
        Storage mGuts{};

    public:
        int getRows() const { return mGuts.getRows(); }
        int getCols() const { return mGuts.getCols(); }
        int getSize() const { return mGuts.getSize(); }
        const Storage& getStorage() const { return mGuts; }
        
        Matrix(int rows,int cols) : mGuts(rows, cols) {}
        Matrix(const Storage& s ) : mGuts(s) {}
        Matrix(const std::initializer_list<std::initializer_list<double>>& m) : mGuts(m) {}

        template<typename S>
        Matrix(const Matrix<S>& s) : mGuts(s.mGuts) {}

        double at(int i, int j) const { return mGuts.at(i,j); }

        double operator()(int i, int j) const { return mGuts(i,j); }
        double& operator()(int i, int j) { return mGuts(i,j); }

        template<typename S>
        friend std::ostream& operator<<(std::ostream& out, const Matrix<S>& m);

        template<typename>
        friend class Matrix;
    };

    template<int i, int j>
    using StackMatrix = Matrix<StackCR<i,j>>;

    using Matrix2x2 = Matrix<StackCR<2,2>>;
    using Matrix3x3 = Matrix<StackCR<3,3>>;
    using Matrix4x4 = Matrix<StackCR<4,4>>;
    using Matrix5x5 = Matrix<StackCR<5,5>>;
    using Matrix6x6 = Matrix<StackCR<6,6>>;
    using Matrix7x7 = Matrix<StackCR<7,7>>;
    using Matrix8x8 = Matrix<StackCR<8,8>>;
    using Matrix9x9 = Matrix<StackCR<9,9>>;
    using Matrix10x10 = Matrix<StackCR<10,10>>;
    using Matrix11x11 = Matrix<StackCR<11,11>>;
    using Matrix12x12 = Matrix<StackCR<12,12>>;
}

#include "matrix.hpp"
