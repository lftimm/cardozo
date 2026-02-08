#include <gtest/gtest.h>
#include <cardozo.h>
#include <random>

using namespace cardozo;

constexpr int rnd_seed{802};
const std::string filePath{"../../tests/matrix_samples/gr_900_900_crg.mm"};

constexpr double tolerance{1.5e-2};

TEST(Algos, SparseCR_Multiplication_CongruentSolver_Match) {

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
