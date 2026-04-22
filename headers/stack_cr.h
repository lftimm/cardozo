#pragma once

#include <array>
#include <cstddef>
#include <initializer_list>
#include <cassert>

#include "dense_cr.h"

namespace cardozo 
{

    template<std::size_t i, std::size_t j>
    class StackCR {
    private:
        std::array<double, i*j> mInternal;
        int mRows;
        int mCols;
        int mSize;

    public:
        int getRows() const { return mRows; }
        int getCols() const { return mCols; }
        int getSize() const { return mSize; }
        const std::array<double, i*j>& getInternal() { return mInternal; }

        StackCR(const std::initializer_list<std::initializer_list<double>>&);
        StackCR(const DenseCR&);

        StackCR(int,int) = delete;
        explicit StackCR(int) = delete;

        double at(int a,int b) const { return mInternal.at(a*mCols+b); }
        double& operator()(int a, int b) { return mInternal[a*mCols+b]; }
        double operator()(int a, int b) const { return mInternal[a*mCols+b]; }
    };

}

#include "stack_cr.hpp"
