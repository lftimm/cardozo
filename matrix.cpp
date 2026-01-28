#include "matrix.h"

#include <stdexcept>
#include <iomanip>
#include <cassert>

namespace cardozo 
{

    Matrix::Matrix(const int i, const int j) noexcept :
        mInternal(std::make_unique<float[]>(i*j)),
        mRows(i),
        mCols(j),
        mSize(i*j) {

    }

    Matrix::Matrix(const Matrix& other) noexcept :
        mInternal(std::make_unique<float[]>(other.mSize)),
        mRows(other.mRows),
        mCols(other.mCols),
        mSize(other.mSize) {

        for(int i = 0; i < other.mSize; i++)
            mInternal[i] = other.mInternal[i];

    }

    Matrix::Matrix(Matrix&& other) noexcept :
        mInternal(std::move(other.mInternal)),
        mRows(other.mRows),
        mCols(other.mCols),
        mSize(other.mSize) {

    }

    float Matrix::at(const int i, const int j) const {

        if(i >= mRows || j >= mCols || i < 0 || j < 0) 
            throw std::out_of_range("Out of range indexing of Matrix.");

        return mInternal[i*mCols+j];
    }

    Matrix& Matrix::operator=(const Matrix& other) {

        if (mSize != other.mSize) {
            mInternal = std::make_unique<float[]>(other.mSize);
        }

        for(int i = 0; i < other.mSize; i++)
            mInternal[i] = other.mInternal[i];

        mRows = other.mRows;
        mCols = other.mCols;
        mSize = other.mSize;

        return *this;
    }

    Matrix& Matrix::operator=(Matrix&& m) {
        mInternal = std::move(m.mInternal);
        mRows = m.mRows;
        mCols = m.mCols;
        mSize = m.mSize;

        m.mRows = 0;
        m.mCols = 0;
        m.mSize = 0;

        return *this;
    }

    Matrix operator+(const Matrix& m, const Matrix& other) {

        assert(
            m.getRows() == other.getRows() && 
            m.getCols() == other.getCols() &&
            "Matrices do not match size"
        );

        const int rows = other.getRows();
        const int cols = other.getCols();

        Matrix r{rows,cols};
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                r(i,j) = m(i,j) + other(i,j);
            }
        }

        return r;
    }

    Matrix operator-(Matrix& m, Matrix& other) {

        assert(
            m.getRows() == other.getRows() && 
            m.getCols() == other.getCols() &&
            "Matrices do not match size"
        );

        const int rows = other.getRows();
        const int cols = other.getCols();

        Matrix r{rows,cols};
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                r(i,j) = m(i,j) - other(i,j);
            }
        }

        return r;
    }

    Matrix operator*(const Matrix& m, float s) {
        assert(
            m.getRows() == m.getRows() && 
            m.getCols() == m.getCols() &&
            "Matrices do not match size"
        );

        const int rows = m.getRows();
        const int cols = m.getCols();

        Matrix r{rows,cols};
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                r(i,j) = s * m(i,j);
            }
        }

        return r;
    }


    Matrix operator*(float s , const Matrix& m) { return m*s; }

    Matrix operator/(const Matrix& m, float s) { return m*(1/s);}

    std::ostream& operator<<(std::ostream& out, Matrix& m) {
        out << "⎡";
        const int width = 4;
        for(int i = 0; i < m.mCols-1; i++) {
            out << std::setw(width);
            out << m(0,i) << " ";
        }
        out << std::setw(width);
        out << m(0,m.mCols-1);
        out <<"⎤\n";

        for(int i = 1; i < m.mRows-1; i++) {
            out << "⎥";

            for(int j = 0; j < m.mCols-1; j++) {
                out << std::setw(width);
                out <<  m(i,j) << " ";
            }
            out << std::setw(width);
            out << m(i,m.mCols-1);
            out << "⎢\n";
        }

        out << "⎣";
        for(int i = 0; i < m.mCols-1; i++) {
            out << std::setw(width);
            out << m(m.mRows-1,i) << " ";
        }
        out << std::setw(width);
        out << m(m.mRows-1, m.mCols-1);
        out << "⎦";

        return out;
    }

}

