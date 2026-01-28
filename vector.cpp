#include "vector.h"
#include <iomanip>

namespace cardozo
{
    Vector::Vector(int l) : 
        Matrix(l,0) {
        mSize = l;
    }

    float& Vector::operator()(int l) {
        return mInternal[l];
    }

    float& Vector::operator()(int l) const {
        return mInternal[l];
    }

    std::ostream& operator<<(std::ostream& out, Vector& v) {
        int width = 4;

        out << "⎡";
        out << std::setw(width);
        out << v(0) << " ";
        out <<"⎤\n";

        for(int i = 1; i <= v.mSize-2; i++) {
            out << "⎥";
            out << std::setw(width);
            out <<  v(i) << " ";
            out << "⎢\n";
        }

        out << "⎣";
        out << std::setw(width);
        out << v(v.mSize-1) << " ";
        out << "⎦";

        return out;
    }
}
