/*
by lftimm
---------
Example 5.2.1 - "O Método De Elementos Finitos Aplicado à Mecânica dos Sólidos" -
Authors: Paulo de Tarso R. Mendonça, Eduardo A. Fancello
Publisher: Orsa Maggiore
*/

#include "cardozo.h"
#include <array>
#include <gtest/gtest.h>

using namespace cardozo;

TEST(FiniteElement, ONE_D_BAR) {
    using NodeINodeJ=std::pair<int,int>;
    using ElasticityArea=std::pair<float,float>;

    // Initial Data
    std::array<float,4> coords{
        0,
        50,
        70,
        90
    };

    std::array<std::pair<int,int>,3> eles{
        NodeINodeJ{0,1},
        NodeINodeJ{1,2},
        NodeINodeJ{2,3},
    };

    std::array<std::pair<float,float>,3> props{
        ElasticityArea{2e5,5},
        ElasticityArea{2e5,10},
        ElasticityArea{2e5,10},
    };

    // Creating Elements
    Matrix2x2 element1 {
        {1,-1},
        {-1,1}
    };
    element1 = element1 * (props[0].first*props[0].second/(coords[1]-coords[0]));

    Matrix2x2 element2 {
        {1,-1},
        {-1,1}
    };
    element2 = element2 * (props[1].first*props[1].second/(coords[2]-coords[1]));

    Matrix2x2 element3 {
        {1,-1},
        {-1,1}
    };
    element3 = element3 * (props[2].first*props[2].second/(coords[3]-coords[2]));
    
    std::array<Matrix2x2,3> elementData{element1,element2,element3};

    // Creating Global Matrix
    Matrix4x4 K{};

    for(int e = 0; e < elementData.size(); ++e) {
        int nodeI = eles[e].first;
        int nodeJ = eles[e].second;

        K(nodeI, nodeI) += elementData[e](0, 0);
        K(nodeI, nodeJ) += elementData[e](0, 1);
        K(nodeJ, nodeI) += elementData[e](1, 0);
        K(nodeJ, nodeJ) += elementData[e](1, 1);
    }

    // Displacement and Forces Vectors
    Vector U{4};
    U(0) = 0;

    Vector F{4};
    F(3) = 500;

    // Boundary conditions
    for(int i = 0; i < 3; i++)
    {
        K(0, i) = 0;
        K(i, 0) = 0;
    }

    // Solve
    Vector u = algos::conjugateGradient(U, K, F);
    std::cerr << u; 

    EXPECT_FLOAT_EQ(u(0),0);
    EXPECT_FLOAT_EQ(u(1),0.025f);
    EXPECT_FLOAT_EQ(u(2),0.030f);
    EXPECT_FLOAT_EQ(u(3),0.035f);
}
