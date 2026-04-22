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

    std::array<float,4> coords{0,50,70,90};

    std::array<std::pair<int,int>,3> eles{
        std::pair<int,int>{0,1},
        std::pair<int,int>{1,2},
        std::pair<int,int>{2,3},
    };

    std::array<std::pair<float,float>,3> props{
        std::pair<float,float>{2e5,5},
        std::pair<float,float>{2e5,10},
        std::pair<float,float>{2e5,10},
    };

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
    
    std::array<Matrix2x2,3> localMtx{element1,element2,element3};

    Matrix4x4 globalMatrix{};

    for(size_t e = 0; e < eles.size(); e++) {
        int dofs[2] = {eles[e].first, eles[e].second};
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                globalMatrix(dofs[i], dofs[j]) += localMtx[e](i, j);
            }
        }
    }

    Vector B{4};
    B(3) = 10000.0; 

    for (int i = 0; i < 4; i++) {
        globalMatrix(0, i) = 0.0;
        globalMatrix(i, 0) = 0.0;
    }
    globalMatrix(0, 0) = 1.0;
    B(0) = 0.0; 

    Vector x{4}; 
    
    EXPECT_NO_THROW(algos::conjugateGradient(x, globalMatrix, B));
    
    EXPECT_GT(x(3), 0.0);
}
