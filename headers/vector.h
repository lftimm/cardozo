#pragma once

#include "dense_cr.h"

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


        const double* getData() const { return mGuts.getInternal();};

        double at(int l) { return mGuts.at(l,0); }

        double& operator()(int i) { return mGuts(i,0);} 
        double operator()(int i) const { return mGuts(i,0);} 

        Vector& operator+=(const Vector& b);
        Vector& operator-=(const Vector& b);
        Vector& operator*=(double s);
        Vector& operator/=(double s);

        friend std::ostream& operator<<(std::ostream&, const Vector&);
    };

    Vector operator+(const Vector& a, const Vector& b);
    Vector operator-(const Vector& a, const Vector& b);

    Vector operator*(const Vector& a, double s);
    Vector operator*(double s, const Vector& a);

    Vector operator/(const Vector& a, double s);


    double dot(const Vector& a, const Vector& b);

    Vector project(const Vector& u, const Vector& a);

    double magnitude(const Vector& v);
    Vector normalize(const Vector& v);
}
