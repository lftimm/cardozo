#include <stdexcept>
#include "sparse_cr.h"

namespace cardozo 
{

    float SparseCR::at(int i, int j) const {
        if(i < 0 || j < 0 || i >= mRows || j >= mCols)
            throw std::out_of_range("Tried accessing matrix out of bounds");

        return operator()(i,j);
    }

    SparseCR::SparseCR(const DenseCR& m) :
        mCols(m.getCols()),
        mRows(m.getRows()),
        mSize(m.getSize()) {

        mRowPtr.push_back(0);
        for(int i = 0; i < m.getRows(); i++) {
            for(int j = 0; j < m.getCols(); j++) {
                float f{m(i,j)};
                if(f != 0) {
                    mData.push_back(f);
                    mColIdx.push_back(j);
                }
            }
            mRowPtr.push_back(static_cast<int>(mData.size()));
        }
    }

    SparseCR::SparseCR(const std::vector<std::vector<float>>& m) :
        mCols(m[0].size()),
        mRows(m.size()),
        mSize(mCols*mRows) {

        mRowPtr.push_back(0);
        for(int i = 0; i < mRows; i++) {
            for(int j = 0; j < mCols; j++) {
                float f{m[i][j]};
                if(f != 0) {
                    mData.push_back(f);
                    mColIdx.push_back(j);
                }
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
