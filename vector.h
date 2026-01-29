#pragma once

#include "densecr.h"

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

    Vector operator/(const Vector& a, const Vector& b);


    float dot(const Vector& a, const Vector& b);

    float magnitude(const Vector& v);
    Vector normalize(const Vector& v);
}
