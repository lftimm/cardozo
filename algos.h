#pragma once

#include "matrix.h"
#include "vector.h"

namespace cardozo 
{
    template<typename S>
    Vector multiply(const Matrix<S>&, const Vector&);

    template<typename S>
    Vector linear_solve_CG(Vector x, Matrix<S>& A, Vector& B, float eps = 1e-5);
}

#include "algos.hpp"
