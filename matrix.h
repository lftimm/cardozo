#pragma once

#include <iostream>
#include <memory>

namespace cardozo 
{
    class Matrix 
    {
    protected:
        std::unique_ptr<float[]> mInternal;
        int mRows;
        int mCols;
        int mSize;

    public:
        Matrix(const int,const int) noexcept;

        Matrix(const Matrix&) noexcept;
        Matrix(Matrix&&) noexcept;

        int getRows() const { return mRows; }
        int getCols() const { return mCols; }
        int getSize() const { return mSize; }

        float at(const int, const int) const;
        
        float& operator()(int i, int j ) const {
            return mInternal[i*mCols+j];
        }

        float& operator()(int i, int j ) {
            return mInternal[i*mCols+j];
        }

        Matrix& operator=(const Matrix&);
        Matrix& operator=(Matrix&&);

        friend std::ostream& operator<<(std::ostream& out, Matrix& m);
    };

    Matrix operator+(const Matrix&, const Matrix&);
    Matrix operator-(const Matrix&);

    Matrix operator*(const Matrix&, float);
    Matrix operator*(float, const Matrix&);

    Matrix operator/(const Matrix&,float);

    using Transform = Matrix;
}
