#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <random>

#include <cardozo.h>
using namespace cardozo;

#define VECTOR_EXPECT_EQ(v1,v2, mes) \
    for(int i = 0; i < kVectorLen; i++)\
        EXPECT_EQ(v1(i), v2(i)) << mes;

constexpr int kVectorLen{1000};
constexpr float kFloatTolerance{1e-4};
constexpr float kScalar{1.5f};
constexpr int kSeed{802};

class VectorTest : public testing::Test {
protected:
    int seed{kSeed};

    Vector v1;
    Vector v2;

    VectorTest() : 
        v1(newRndVec()),
        v2(newRndVec()) {
            
    }

    Vector newRndVec() {
        
        Vector v{kVectorLen};
        std::mt19937 rng(seed++);

        for(int i = 0; i < kVectorLen; i++)
            v(i) = static_cast<float>(rng() % kVectorLen);

        return v;
   }
};

TEST_F(VectorTest, VECTOR_SUM_MINUS_CANCEL) {
    std::string message = "Vector Sum and Subtraction not canceling out.";

    Vector sum = v1 + v2; 
    Vector commSum = v2 + v1;
    VECTOR_EXPECT_EQ(sum, commSum, "Commutative Property Not Holding For Sum");

    Vector subtract = sum - v2;


    VECTOR_EXPECT_EQ(v1, subtract, message);
}

TEST_F(VectorTest, VECTOR_SCALAR_MULTIPLY_DIVISION_CANCEL) {
    std::string message = "Vector Scalar Multiplcation and Division not Canceling out.";

    Vector multiply = v1 * kScalar;
    Vector divide = multiply / kScalar;
     
    VECTOR_EXPECT_EQ(v1, divide, message);
}

TEST_F(VectorTest, VECTOR_NORMALIZED_MAGNITUDE_EQ_1) {
    float l = magnitude(normalize(v1));

    ASSERT_NEAR(l, 1.f, kFloatTolerance) << "Magnitude of Normalized Vector Not Equal to 1.0f";
}

TEST_F(VectorTest, VECTOR_COPY_EQ_ORIGINAL) {
    
    Vector copy = v1;
    VECTOR_EXPECT_EQ(v1, copy, "Copy is Different From Original");

}

TEST_F(VectorTest, VECTOR_MOVE_CONSTRUCTOR) {
    
    Vector moved{kVectorLen};
    moved = std::move(v1); 

    EXPECT_EQ(v1.getLength(), 0) << "Moved Length wasn't set to 0";

    EXPECT_DEATH({v1(0);}, "");
}

TEST_F(VectorTest, VECTOR_SUM_ASSIGNMENT) {
    Vector summed = v1 + v2;

    Vector copy = v1;  
    copy += v2;
   
    VECTOR_EXPECT_EQ(copy, summed, "Sum Assignment Different than Direct Sum");
}

TEST_F(VectorTest, VECTOR_MINUS_ASSIGNMENT) {
    Vector subtracted = v1 - v2;

    Vector copy = v1;  
    copy -= v2;
   
    VECTOR_EXPECT_EQ(copy, subtracted, "Subtract Assignment Different than Direct Subtraction");
}

TEST_F(VectorTest, VECTOR_TIMES_SCALAR_ASSIGNMENT) {

    Vector multiplied = v1 * kScalar;

    Vector copy = v1;  
    copy *= kScalar;
   
    VECTOR_EXPECT_EQ(copy, multiplied, "Times Assignment Different than Direct Multiplication");

    Vector multiplied2 = kScalar * v1;
    VECTOR_EXPECT_EQ(multiplied, multiplied2, "Commutative Property Not Holding For Multiplication");
}

TEST_F(VectorTest, VECTOR_DIVIDED_SCALAR_ASSIGNMENT) {

    Vector divided = v1 / kScalar;

    Vector copy = v1;  
    copy /= kScalar;
   
    VECTOR_EXPECT_EQ(copy, divided, "Divide Assignment Different than Direct Division");
}
