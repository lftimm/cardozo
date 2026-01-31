#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

namespace cardozo
{
    class DenseCR {
    private:
        std::unique_ptr<float[]> mInternal;
        int mRows;
        int mCols;
        int mSize;

    public:
        int getRows() const { return mRows; }
        int getCols() const { return mCols; }
        int getSize() const { return mSize; }

        DenseCR(int,int);
        explicit DenseCR(int);
        DenseCR(const std::initializer_list<std::initializer_list<float>>&);


        DenseCR(const DenseCR&);
        DenseCR(DenseCR&&);

        DenseCR& operator=(const DenseCR&);
        DenseCR& operator=(DenseCR&&);

        ~DenseCR() = default;

        float at(int,int) const;
        float& operator()(int i, int j);
        float operator()(int i, int j) const;
    };
}
