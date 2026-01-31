#include "sparse_cr.h"
#include <algorithm>
#include <initializer_list>
#include <numeric>
#include <stdexcept>

namespace cardozo 
{

    float SparseCR::at(int i, int j) const {
        if(i < 0 || j < 0 || i >= mRows || j >= mCols)
            throw std::out_of_range("Tried accessing matrix out of bounds");

        return operator()(i,j);
    }

    SparseCR::SparseCR(const std::initializer_list<std::initializer_list<float>>& m) :
        mRows(m.size()),
        mCols(m.size() == 0 ? 0 : m.begin()->size()),
        mSize(mCols*mRows) {

        const int nz_e = std::accumulate(m.begin(), m.end(),
        0, [width = mCols](int sum, const auto& r) {
                if(r.size() != width)
                    throw std::runtime_error("Passed an irregular matrix, be sure to pass a rectangular matrix");
                return sum + std::count_if(r.begin(), r.end(), [](const auto c){ return c != 0.f;});
        });

        mData.reserve(nz_e);
        mColIdx.reserve(nz_e);
        mRowPtr.reserve(mRows+1);

        mRowPtr.push_back(0);

        for(const auto& r : m) {
            int col{};
            for(const auto c : r)
            {
                if(c!=0)
                {
                    mData.push_back(c);
                    mColIdx.push_back(col);
                }
                col++;
            }
            mRowPtr.push_back(static_cast<int>(mData.size()));
        } 

    }


    float SparseCR::operator()(int i, int j) const {
        const int row_start = mRowPtr[i];
        const int row_end = mRowPtr[i+1];

        for(int r = row_start; r < row_end; r++) {
            if(mColIdx[r] == j)
                return mData[r];
        };

        return 0;
    }
}
