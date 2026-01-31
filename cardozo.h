/* Cardozo - Linear Algebra Library */
#ifndef CARDOZO_H
#define CARDOZO_H
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cassert>
#include <array>
#include <sstream>

// >>> headers/dense_cr.h

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
        DenseCR(const std::vector<std::vector<float>>&);


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

// >>> headers/stack_cr.h

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

// >>> headers/matrix.h
#include <vector>
#include <iomanip>


namespace cardozo 
{
    template<typename Storage = DenseCR>
    class Matrix {
    private:
        Storage mGuts{};

    public:
        int getRows() const { return mGuts.getRows(); }
        int getCols() const { return mGuts.getCols(); }
        int getSize() const { return mGuts.getSize(); }
        
        Matrix(int rows,int cols) : mGuts(rows, cols) {}
        Matrix(const Storage& s ) : mGuts(s) {}
        Matrix(const std::vector<std::vector<float>>& m) : mGuts(m) {}

        template<typename S>
        Matrix(const Matrix<S>& s) : mGuts(s.mGuts) {}

        float at(int i, int j) const { return mGuts.at(i,j); }

        float operator()(int i, int j) const { return mGuts(i,j); }
        float& operator()(int i, int j) { return mGuts(i,j); }

        template<typename S>
        friend std::ostream& operator<<(std::ostream& out, const Matrix<S>& m);

        template<typename>
        friend class Matrix;
    };
}


// >>> src/matrix.hpp

namespace cardozo
{
    template<int i, int j>
    using Transform = Matrix<StackCR<i,j>>;

    template<typename S>
    Matrix<S> operator+(const Matrix<S>& m, const Matrix<S>& other) {

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

    template<typename S>
    Matrix<S> operator*(const Matrix<S>& m, float s) {
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

    template<typename S>
    Matrix<S> operator*(float s , const Matrix<S>& m) { return m*s; }

    template<typename S>
    Matrix<S> operator/(const Matrix<S>& m, float s) { return m*(1/s);}

    template<typename S>
    std::ostream& operator<<(std::ostream& out, const Matrix<S>& m) {
        out << "⎡";
        const int width = 4;
        for(int i = 0; i < m.getCols()-1; i++) {
            out << std::setw(width);
            out << m(0,i) << " ";
        }
        out << std::setw(width);
        out << m(0,m.getCols()-1);
        out <<"⎤\n";

        for(int i = 1; i < m.getRows()-1; i++) {
            out << "⎥";

            for(int j = 0; j < m.getCols()-1; j++) {
                out << std::setw(width);
                out <<  m(i,j) << " ";
            }
            out << std::setw(width);
            out << m(i,m.getCols()-1);
            out << "⎢\n";
        }

        out << "⎣";
        for(int i = 0; i < m.getCols()-1; i++) {
            out << std::setw(width);
            out << m(m.getRows()-1,i) << " ";
        }
        out << std::setw(width);
        out << m(m.getRows()-1, m.getCols()-1);
        out << "⎦";

        return out;
    }
}

// >>> headers/vector.h


namespace cardozo 
{
    class Vector  
    {
        DenseCR mGuts;

    public:
        int getLength() const { return mGuts.getSize(); }

        Vector(int l) : mGuts(l) { };

        Vector(const Vector&) = default;
        Vector(Vector&&) = default;
        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) = default;


        float at(int l) { return mGuts.at(l,0); }

        float& operator()(int i) { return mGuts(i,0);} 
        float operator()(int i) const { return mGuts(i,0);} 

        Vector& operator+=(const Vector& b);
        Vector& operator-=(const Vector& b);
        Vector& operator*=(float s);
        Vector& operator/=(float s);

        friend std::ostream& operator<<(std::ostream&, const Vector&);
    };

    Vector operator+(const Vector& a, const Vector& b);
    Vector operator-(const Vector& a, const Vector& b);

    Vector operator*(const Vector& a, float s);
    Vector operator*(float s, const Vector& a);

    Vector operator/(const Vector& a, float s);


    float dot(const Vector& a, const Vector& b);

    float magnitude(const Vector& v);
    Vector normalize(const Vector& v);
}

// >>> headers/algos.h

namespace cardozo::algos
{
    template<typename S>
    Vector multiply(const Matrix<S>&, const Vector&);

    template<typename S>
    Vector congruentGradient(Vector x, Matrix<S>& A, Vector& B, float eps = 1e-5);
}


// >>> src/algos.hpp
#include <sstream>

namespace cardozo::algos 
{
    template<typename S>
    Vector multiply(const Matrix<S>& a, const Vector& b) {
        int cols = a.getCols();
        int rows = a.getRows();
        int len = b.getLength();
    
        if (cols != len)
        {
            std::stringstream ss{};
            ss << "multiply: matrix and vector are incompatible\n"
               << "M shape: (" << a.getRows() << ", " << a.getCols() << ")\n"
               << "V len: (" << b.getLength() << ")\n"
               ;
    
            throw std::out_of_range(ss.str());
        }
    
        Vector res{rows};
        for (int i = 0 ; i < rows ; i++) {
            float acc = 0;
            for (int j = 0 ; j < cols ; j++) {
                acc += a(i,j) * b(j);
            }
            res(i) = acc;
        }
    
        return res;
    }
    
    
    template<typename S>
    Vector congruentGradient(Vector x, Matrix<S>& A, Vector& B, float eps) {

        Vector res = multiply(A,x) - B;
        Vector delta = res * -1;
    
        while (true) 
        {
            if (magnitude(res) <= eps) {
                return x;
            }
    
            Vector D = multiply(A,delta);
            float beta = dot(res,delta) * (-1/dot(delta,D));
            x += delta * beta;
            
    
            res = multiply(A,x) - B;
            float chi = dot(res,D) * (1/dot(delta,D));
            delta = delta*chi - res;
        }
    }
}

// >>> headers/sparse_cr.h

#include <vector>

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
            SparseCR(const DenseCR& m);
            SparseCR(const std::vector<std::vector<float>>& m);

            int getRows() const { return mRows; }
            int getCols() const { return mCols; }
            int getSize() const { return mSize; }

            float& operator()(int,int) = delete;
            float operator()(int,int) const;
            float at(int,int) const;
    };
 
}

#endif // CARDOZO_H

#ifdef CARDOZO_IMPLEMENTATION

// >>> src/dense_cr.cpp
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

    DenseCR::DenseCR(const std::vector<std::vector<float>>& v) :
        mInternal(std::make_unique<float[]>(v.size()*v[0].size())),
        mRows(v.size()), 
        mCols(v[0].size()),
        mSize(mRows*mCols) {
        
        for(int i = 0; i < mRows; i++) {
            for(int j = 0; j < mCols; j++) {
                mInternal[i*mCols + j] = v[i][j];
            }
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

#endif // CARDOZO_IMPLEMENTATION
