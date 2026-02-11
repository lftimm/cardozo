#pragma once
#include "dense_cr.h"
#include "matrix.h"
#include "vector.h"

namespace cardozo::algos
{
    template<typename S>
    Vector conjugateGradient(Vector x, const Matrix<S>& A, const Vector& B, float eps = 1e-3);


    Matrix<DenseCR> transpose(const Matrix<DenseCR>& m);
}

#include "algos.hpp"
