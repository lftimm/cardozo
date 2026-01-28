#pragma once

#include "matrix.h"
#include "vector.h"

namespace cardozo 
{
    Vector multiply(const Matrix&, const Vector&);

    Vector linear_solve_CG(Vector, Matrix&, Vector&, float eps = 1e-5);
}
