#pragma once

#include "densecr.h"

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
        
        Matrix(int rows,int cols) : mGuts(rows, cols) {} ;
        float at(int i, int j) const { return mGuts.at(i,j); }

        float operator()(int i, int j) const { return mGuts(i,j); }
        float& operator()(int i, int j) { return mGuts(i,j); }

        template<typename S>
        friend std::ostream& operator<<(std::ostream& out, const Matrix<S>& m);
    };
}

#include "matrix.hpp"
