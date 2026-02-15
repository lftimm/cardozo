#pragma once

#include <stdexcept>
#include <vector>
#include "dense_cr.h"

namespace cardozo 
{
    class SparseCR {
        private:
            std::vector<double> mData;
            std::vector<int> mColIdx;
            std::vector<int> mRowPtr;
            
            int mRows;
            int mCols;
            int mSize;

        public:

            explicit SparseCR(int) = delete;
            SparseCR(int,int) { throw std::logic_error("SparseCR Shouldn't be modified."); }

            SparseCR(const std::initializer_list<std::initializer_list<double>>&);
            SparseCR(const DenseCR& m);

            int getRows() const { return mRows; }
            int getCols() const { return mCols; }
            int getSize() const { return mSize; }

            const std::vector<double>& getData() const { return mData; }
            const std::vector<int>& getColIdx() const { return mColIdx; }
            const std::vector<int>& getRowPtr() const { return mRowPtr; }

            double& operator()(int,int) { throw std::logic_error("SparseCR Shouldn't be modified."); };
            double operator()(int,int) const;
            double at(int,int) const;
            
            template<typename S> 
            friend class Matrix;
    };
 
}
