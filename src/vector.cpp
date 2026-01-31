#include <iomanip>
#include <cmath>
#include <iostream>
#include <cassert>

#include "../headers/vector.h"

namespace cardozo
{
    Vector& Vector::operator+=(const Vector& b) {
        assert(getLength() == b.getLength() && "Must be of equal size");
        
        for(int i = 0; i < getLength(); i++)  {
            mGuts(i,0) += b(i);
        }

        return *this;
    }

    Vector& Vector::operator-=(const Vector& b) {
        assert(getLength() == b.getLength() && "Must be of equal size");
        
        for(int i = 0; i < getLength(); i++)  {
            mGuts(i,0) -= b(i);
        }

        return *this;
    }

    Vector& Vector::operator*=(float s) {
        for(int i = 0; i < getLength(); i++)  {
            mGuts(i,0) *= s;
        }

        return *this;
    }
    
    Vector& Vector::operator/=(float s) {
        for(int i = 0; i < getLength(); i++)  {
            mGuts(i,0) *= 1/s;
        }

        return *this;
    }

    std::ostream& operator<<(std::ostream& out, const Vector& v) {
        int width = 4;

        out << "⎡";
        out << std::setw(width);
        out << v(0) << " ";
        out <<"⎤\n";

        for(int i = 1; i <= v.getLength()-2; i++) {
            out << "⎥";
            out << std::setw(width);
            out <<  v(i) << " ";
            out << "⎢\n";
        }

        out << "⎣";
        out << std::setw(width);
        out << v(v.getLength()-1) << " ";
        out << "⎦";

        return out;
    }

    Vector operator+(const Vector& a, const Vector& b) {
        assert(a.getLength() == b.getLength() && "Must be of same size");

        Vector r{a.getLength()};
        for(int i = 0; i < a.getLength(); i++)
            r(i) = a(i) + b(i);

        return r;
    }

    Vector operator-(const Vector& a, const Vector& b) {
        assert(a.getLength() == b.getLength() && "Must be of same size");

        Vector r{a.getLength()};
        for(int i = 0; i < a.getLength(); i++)
            r(i) = a(i) - b(i);

        return r;
    }

    Vector operator*(const Vector& a, float s) {
        Vector r{a.getLength()};

        for(int i = 0; i < a.getLength(); i++)
            r(i) = a(i) * s;

        return r;
    }

    Vector operator*(float s, const Vector& a) { return a * s; }
    Vector operator/(const Vector& a, float s) { return a * (1/s); }


    float dot(const Vector& a, const Vector& b) {
        assert(a.getLength() == b.getLength() && "Must be of equal size");

        float acc{};
        for(int i = 0; i < a.getLength(); i++)  {
            acc += a(i) * b(i);
        }

        return acc;
    }

    float magnitude(const Vector& v) {
        float acc{};
        for(int i = 0; i < v.getLength(); i++)  {
            acc += pow(v(i),2);
        }
        return std::sqrt(acc);
    }

    Vector normalize(const Vector& v) {
        float mag = magnitude(v);
        Vector r{v.getLength()};
        for(int i = 0; i < v.getLength(); i++)  {
            r(i) = v(i) / mag;
        }

        return r;
    }
}
