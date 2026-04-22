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
            std::vector<std::tuple<int,int,double>> mPending;
            
            int mRows;
            int mCols;
            int mSize;

            bool mCompressed;

        public:

            explicit SparseCR(int) = delete;

            SparseCR(int,int);

            SparseCR(const std::initializer_list<std::initializer_list<double>>&);
            SparseCR(const DenseCR& m);

            int getRows() const { return mRows; }
            int getCols() const { return mCols; }
            int getSize() const { return mSize; }

            const std::vector<double>& getData() const { return mData; }
            const std::vector<int>& getColIdx() const { return mColIdx; }
            const std::vector<int>& getRowPtr() const { return mRowPtr; }

            double& operator()(int,int);
            double operator()(int,int) const;
            double at(int,int) const;
            
            template<typename S> 
            friend class Matrix;
    };
 
}
