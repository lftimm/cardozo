#pragma once

#include <initializer_list>
#include <memory>

namespace cardozo
{
    class DenseCR {
    private:
        std::unique_ptr<double[]> mInternal;
        int mRows;
        int mCols;
        int mSize;

    public:
        int getRows() const { return mRows; }
        int getCols() const { return mCols; }
        int getSize() const { return mSize; }
        const double* getInternal() const { return mInternal.get(); }

        DenseCR(int,int);
        explicit DenseCR(int);
        DenseCR(const std::initializer_list<std::initializer_list<double>>&);


        DenseCR(const DenseCR&);
        DenseCR(DenseCR&&);

        DenseCR& operator=(const DenseCR&);
        DenseCR& operator=(DenseCR&&);

        ~DenseCR() = default;

        double at(int,int) const;
        double& operator()(int i, int j);
        double operator()(int i, int j) const;
        
    };
}
