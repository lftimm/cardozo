#include "dense_cr.h"
#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace cardozo
{
    DenseCR::DenseCR(int rows, int cols) :
        mInternal(std::make_unique<float[]>(rows*cols)),
        mRows(rows),
        mCols(cols),
        mSize(rows*cols) {

    }

    DenseCR::DenseCR(int length) :
        mInternal(std::make_unique<float[]>(length)),
        mRows(length),
        mCols(1),
        mSize(length) {

    }

    DenseCR::DenseCR(const DenseCR& c) :
        mInternal(std::make_unique<float[]>(c.mSize)),
        mRows(c.mRows),
        mCols(c.mCols),
        mSize(c.mSize) {

        for(int i = 0; i < mRows; i++) {
            for(int j = 0; j < mCols; j++) {
                mInternal[i*mCols + j] = c.mInternal[i*mCols + j];
            }
        }
    }

    DenseCR::DenseCR(DenseCR&& o):
        mInternal(std::move(o.mInternal)),
        mRows(o.mRows),
        mCols(o.mCols),
        mSize(o.mSize) {
            o.mInternal = nullptr;
            o.mRows = 0;
            o.mCols = 0;
            o.mSize = 0;
    }

    DenseCR::DenseCR(const std::initializer_list<std::initializer_list<float>>& v) :
        mInternal(std::make_unique<float[]>(v.size() == 0 ? 0 : v.begin()->size())),
        mRows(v.size()), 
        mCols(v.size() == 0 ? 0 : v.begin()->size()),
        mSize(mRows*mCols) {
        
        int idx{};
        for(const auto&  r : v)
        {
            if(r.size() != mCols)
                throw std::runtime_error("Passed an irregular matrix, be sure to pass a rectangular matrix");

            for(const auto c : r)
                mInternal[idx++] = c;
        }
    }

    DenseCR& DenseCR::operator=(const DenseCR& c) {
        mInternal = std::make_unique<float[]>(c.mSize);

        for(int i = 0; i < mRows; i++) {
            for(int j = 0; j < mCols; j++) {
                mInternal[i*mCols + j] = c.mInternal[i*mCols + j];
            }
        }

        mRows = c.mRows;
        mCols = c.mCols;
        mSize = c.mSize;

        return *this;
    }

    DenseCR& DenseCR::operator=(DenseCR&& o) {
        mInternal = std::move(o.mInternal);
        mRows = o.mRows;
        mCols = o.mCols;
        mSize = o.mSize;

        o.mInternal = nullptr;
        o.mRows = 0;
        o.mCols = 0;
        o.mSize = 0;

        return *this;
    }

    float& DenseCR::operator()(int i, int j) {
        return mInternal[i*mCols+j]; 
    }

    float DenseCR::operator()(int i, int j) const {
        return mInternal[i*mCols+j]; 
    }

    float DenseCR::at(int i, int j) const {
        if(i < 0 || j < 0 || i >= mRows || j >= mCols)
            throw std::out_of_range("Tried to read out of bounds");

        return mInternal[i*mCols+j]; 
    }
}
