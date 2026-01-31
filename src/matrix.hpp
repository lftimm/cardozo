#pragma once
#include "matrix.h"

namespace cardozo
{

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
