#pragma once

#include "matrix.h"

namespace cardozo 
{
    class Vector : public Matrix 
    {
    public:
        Vector(int l);
        float& operator()(int i);
        float& operator()(int i) const;
        friend std::ostream& operator<<(std::ostream&, Vector&);
    };
}
