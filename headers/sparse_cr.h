#pragma once

#include <vector>
#include "dense_cr.h"

namespace cardozo 
{
    class SparseCR {
        private:
            std::vector<float> mData;
            std::vector<int> mColIdx;
            std::vector<int> mRowPtr;
            
            int mRows;
            int mCols;
            int mSize;

        public:
            SparseCR(const std::initializer_list<std::initializer_list<float>>&);

            int getRows() const { return mRows; }
            int getCols() const { return mCols; }
            int getSize() const { return mSize; }

            float& operator()(int,int) = delete;
            float operator()(int,int) const;
            float at(int,int) const;
    };
 
}
