#pragma once

#include <array>
#include <vector>
#include <cassert>

namespace cardozo 
{
    template<std::size_t i, std::size_t j>
    class StackCR {
    private:
        std::array<float, i*j> mInternal{};
        int mRows{static_cast<int>(i)};
        int mCols{static_cast<int>(j)};
        int mSize{static_cast<int>(i*j)};

    public:
        int getRows() const { return mRows; }
        int getCols() const { return mCols; }
        int getSize() const { return mSize; }

        StackCR(int,int) = delete;
        explicit StackCR(int) = delete;
        StackCR(const std::vector<std::vector<float>>&);
        StackCR(const StackCR&) = default;
        StackCR(StackCR&&) = default;
        StackCR& operator=(const StackCR&) = default;
        StackCR& operator=(StackCR&&) = default;
        ~StackCR() = default;

        float at(int a,int b) const { return mInternal.at(a*mCols+b); }
        float& operator()(int a, int b) { return mInternal[a*mCols+b]; }
        float operator()(int a, int b) const { return mInternal[a*mCols+b]; }
    };

    template<std::size_t i, std::size_t j>
    StackCR<i,j>::StackCR(const std::vector<std::vector<float>>& m) {

        assert(m.size() == i && m[0].size() == j && "Matrices must match size");

        for(int a = 0; a < mRows; a++) {
            for(int b = 0; b < mCols; b++) {
                mInternal[a*mCols+b] = m[a][b];
            }
        }

    }
}
