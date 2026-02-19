# cardozo

A simple to use and flexibile math library for graphics, science and engineering simulation. 
This library is going to be used for my Bachelor's Thesis [Multicore and GPU Accelerated FEM].

## Installation
CMake was used so it should be straight-forward.
```sh
git clone https://github.com/lftimm/cardozo
cd cardozo/build
sudo make install
```

## Notes/Commentary
* Unless stated otherwise suppose all storage backends are heap allocated.
* I focused mainly on decoupling storage from implementation and numerical methods, focusing on const correctness and prefering non-member functions for most cases.
* The templated strategy pattern should not bring performance overheads, although i have not benchmarked yet.
* When building cardozo bundles all headers in a single .h file using a custom python script that does a topological ordering of all header fields and joins them all. That's why the project's structure does not mirror the final file.

## Examples

```cpp
#include <cardozo.h>
using namespace cardozo;

int main() {
    Matrix a{2,2}; // Matrix of size 2x2 using the default backend (Dense Column Row)
    a(0,0) = 1; 
    a(0,1) = 0;
    a(1,0) = 0;
    a(0,1) = 1;

    Matrix<DenseCR> b{ // Matrix using the DenseCR (Dense Column Row) backend, initialized with an initializer list
        {1,0},
        {0,1}
    };

    Matrix<SparseCR> c {a}; // Matrix using the alternative backend (Compressed Sparse Row)
    Matrix d { // Matrix using DenseCR as backend and initialized with initializer list
        {1,0},
        {0,1}
    };

    // Stack allocated Matrices, more aliases for different sizes were also provided.
    Matrix<StackCR<2,2>> st1{a};
    Matrix2x2 st2{a}; 

    // Vector usage (they use DenseCR as their backend)
    Vector v{2};
    v(0) = 1;
    v(1) = 2;
    
    Vector x{2};
    x(0) = 0;
    x(1) = 0;

    std::cout << algos::conjugateGradient(x,a,v)<< "\n"; // Solving the linear system with the Conjugate Gradient Method

    std::cout << v+x << "\n"; // Sum of vectors 
```
### Sources
[Wikipedia, Sparse Matrix](https://en.wikipedia.org/wiki/Sparse_matrix)

[Compressed Sparse Row (CSR) | Sparse Matrices | with implementation in C ](https://www.youtube.com/watch?v=a2LXVFmGH_Q)

[Wikipedia, Conjugate Gradient Method](https://en.wikipedia.org/wiki/Conjugate_gradient_method)

[Introduction to Mathematical Optimization
with Python, #5.2 Linear Conjugate Gradient Algorithm](https://indrag49.github.io/Numerical-Optimization/conjugate-gradient-methods-1.html#linear-conjugate-gradient-algorithm)

[Numerical Linear Algebra](https://youtube.com/playlist?list=PLAVG7GMBpcYArR9QLXm3DVvqYhRdF6Tsj&si=O8atsIv8dxUAABEO)

[GoogleTest Primer](https://google.github.io/googletest/primer.html)

[Painless Conjugate Gradient](https://math.nyu.edu/~greengar/painless-conjugate-gradient.pdf)

[Wikipedia, Cholesky Decomposition](https://en.wikipedia.org/wiki/Cholesky_decomposition)

[Wikipedia, LU Decomposition](https://en.wikipedia.org/wiki/LU_decomposition)

[Doolittle Algorithm | LU Decomposition](https://www.geeksforgeeks.org/dsa/doolittle-algorithm-lu-decomposition/)


### Why cardozo?
https://pt.wikipedia.org/wiki/Joaquim_Cardozo 
