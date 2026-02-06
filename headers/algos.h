#pragma once
#include "matrix.h"
#include "vector.h"

namespace cardozo::algos
{
    template<typename S>
    Vector congruentGradient(Vector x, Matrix<S>& A, Vector& B, float eps = 1e-3);
}

#include "algos.hpp"
