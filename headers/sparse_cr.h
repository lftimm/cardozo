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
            SparseCR(const DenseCR& m);

            int getRows() const { return mRows; }
            int getCols() const { return mCols; }
            int getSize() const { return mSize; }

            const std::vector<float>& getData() const { return mData; }
            const std::vector<int>& getColIdx() const { return mColIdx; }
            const std::vector<int>& getRowPtr() const { return mRowPtr; }

            float& operator()(int,int) = delete;
            float operator()(int,int) const;
            float at(int,int) const;
            
            template<typename S> 
            friend class Matrix;
    };
 
}
