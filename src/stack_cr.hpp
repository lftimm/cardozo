#pragma once

#include <iostream>

#include "stack_cr.h"
#include "dense_cr.h"

namespace cardozo 
{

    template<std::size_t i, std::size_t j>
    StackCR<i,j>::StackCR(const std::initializer_list<std::initializer_list<double>>& m):
        mInternal(),
        mRows(static_cast<int>(i)),
        mCols(static_cast<int>(j)),
        mSize(mRows*mCols) {

        assert(m.size() == 0 || (m.size() == i && m.begin()->size() == j && "Matrices must match size"));

        std::size_t a{};
        std::size_t b{};
        for (const auto& r : m)
        {
            b = 0;
            for (const auto c : r )
            {
                mInternal[a*mCols+b] = c;
                b++;
            }
            a++;
        }
    }

    template<std::size_t i, std::size_t j>
    StackCR<i,j>::StackCR(const DenseCR& other) :
        mInternal(),
        mRows(static_cast<int>(i)),
        mCols(static_cast<int>(j)),
        mSize(mRows*mCols) {


        assert(mRows == other.getRows() && mCols == other.getCols() && "Matrices must match size." );

        for(int r = 0; r < mRows; r++)
        {
            for(int c = 0; c < mCols; c++)
            {
                mInternal[r*mCols + c] = other(r,c);
            }
        }

    }
}

