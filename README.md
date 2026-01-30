# cardozo
---

A simple to use and flexbile math library to be used for simulation and graphics. 
This library is going to be used for my Bachelor's Thesis [Multicore and GPU Accelerated FEM].

## Future goals
Adding compilation options targeting OpenMP and Nvidia CUDA.
More Matrix Storage Backends, looking into adding stack allocated matrices.
More solvers and manners of multiplying.
A matrix dispatcher, able to deploy the best backend based on the characterstics of the matrix.
Helper functions.

## Notes/Commentary
* Unless stated otherwise suppose all storage backends are heap allocated.
* I focused mainly on decoupling storage from implementation, focusing on const correctness and prefering non-member functions for most cases.
* The templated strategy pattern should not bring performance overheads, although i have not tested, worth compiling with -O3 and seeing.

## Examples

```cpp
#include "algos.h"
#include "matrix.h"
#include "sparse_cr.h"
#include "vector.h"

int main() {
    cardozo::Matrix a{2,2}; // Matrix of size 2x2 using the default backend (Dense Matrix)
    a(0,0) = 1; 
    a(0,1) = 0;
    a(1,0) = 0;
    a(0,1) = 1;

    cardozo::Matrix<cardozo::DenseCR> b{ // Matrix using the default backend, initialized with an Array of Arrays
        {1,0},
        {0,1}
    };

    cardozo::Matrix<cardozo::SparseCR> c {a}; // Matrix using the alternative backend (Compressed Sparse Row)
    cardozo::Matrix d{ // Matrix using CSR as backend and initialized from an AoA
        {1,0},
        {0,1}
    };

    // Vector usage (they use DenseCR as their backend)
    cardozo::Vector v{2};
    v(0) = 1;
    v(1) = 2;
    
    cardozo::Vector x{2};
    x(0) = 0;
    x(1) = 0;

    std::cout << cardozo::linear_solve_CG(x,a,v)<< "\n"; // Solving the linear system with the Conjugate Gradient Method

    std::cout << v+x << "\n"; // Sum of vectors 
    /*
    Other available operations:

    Vector - Vector
    Vector * Vector
    dot(Vector, Vector)
    Vector * float 
    scalar * Vector
    Vector / float
    multiply(Matrix<S>, Vector)

    */
```

### Why cardozo?
https://pt.wikipedia.org/wiki/Joaquim_Cardozo 
