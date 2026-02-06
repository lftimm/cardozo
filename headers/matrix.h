#pragma once
#include <initializer_list>
#include <sys/types.h>

#include "dense_cr.h"
#include "stack_cr.h"
#include "vector.h"

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
        Matrix(const std::initializer_list<std::initializer_list<float>>& m) : mGuts(m) {}

        template<typename S>
        Matrix(const Matrix<S>& s) : mGuts(s.mGuts) {}

        float at(int i, int j) const { return mGuts.at(i,j); }

        float operator()(int i, int j) const { return mGuts(i,j); }
        float& operator()(int i, int j) { return mGuts(i,j); }

        template<typename S>
        friend std::ostream& operator<<(std::ostream& out, const Matrix<S>& m);

        template<typename>
        friend class Matrix;
    };

    template<int i, int j>
    using Transform = Matrix<StackCR<i,j>>;
}

#include "matrix.hpp"
