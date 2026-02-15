#include <gtest/gtest.h>
#include <cardozo.h>
#include <random>

using namespace cardozo;

constexpr int rnd_seed{802};
const std::string filePath{"../../tests/matrix_samples/gr_900_900_crg.mm"};

constexpr double tolerance{1.5e-2};

TEST(Algos, DISABLED_SPARSECR_MULTIPLICATION_CONGRUENTSOLVER_MATCH) {

    std::mt19937 rng{rnd_seed};
    std::normal_distribution<float> dist{0,1e2};

    Matrix m = utils::from_mmt_file(filePath);

    Vector v{m.getRows()};
    for(int i = 0; i < v.getLength(); i++)
        v(i) = dist(rng);

    Vector b{multiply(m,v)};
    Vector x{v.getLength()};  

    for(int i = 0; i < x.getLength(); i++) 
        x(i) = dist(rng);

    Vector result = algos::conjugateGradient(x, m, b);

    for(int i = 0; i < result.getLength(); i++)
    {
        ASSERT_NEAR(v(i), result(i), tolerance) 
            << "Sparse Matrix Conjugate Solver not Passing the Ax=B test at i="<<i<<"."
            <<" Expected:" << v(i) <<", Got:" << result(i);
    }

}

TEST(Algos, MAT_POSITIVE_DEFINED)
{

    Matrix<DenseCR> P{
        {2,1,0},
        {1,1,0},
        {0,0,3},
    };

    auto l = algos::cholesky_decompose(P);
    auto l_t = algos::transpose(l);

    auto r = algos::multiply(l, l_t);

    for(int i = 0; i < P.getRows(); i++)
    {
        for(int j = 0; j < P.getCols(); j++)
        {
            EXPECT_FLOAT_EQ(P(i,j), r(i,j)) << "Positive-definite test at (" << i << ", " << j << ")\n failed";
        }
    }
}

TEST(Algos, LU_DECOMPOSITION) 
{

    Matrix<DenseCR> A{{
      {2,-1,-2},
      {-4,6,3},
      {-4,-2,8}
    }};

    Matrix<DenseCR> L{{
        {1,0,0},
        {-2,1,0},
        {-2,-1,1}
    }};

    Matrix<DenseCR> U{{
        {2,-1,-2},
        {0,4,-1},
        {0,0,3}
    }};

    std::pair<Matrix<DenseCR>,Matrix<DenseCR>> lu = algos::lu_decompose(A);
    auto l = lu.first;
    auto u = lu.second;

    for(int i = 0; i < U.getRows(); i++)
    {
        for(int j = 0; j < A.getRows(); j++)
        {
            EXPECT_FLOAT_EQ(l(i,j), L(i,j)) << "L decompose failed at (" << i << ", " << j << ")\n";
            EXPECT_FLOAT_EQ(u(i,j), U(i,j)) << "U decompose failed at (" << i << ", " << j << ")\n";;
        }
    }

    
}
