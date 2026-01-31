#pragma once
#include "sparse_cr.h"
#include "matrix.h"
#include "vector.h"

namespace cardozo::algos
{
    template<typename S>
    Vector multiply(const Matrix<S>&, const Vector&);

    template<typename S>
    Vector congruentGradient(Vector x, Matrix<S>& A, Vector& B, float eps = 1e-5);
}

#include "algos.hpp"
