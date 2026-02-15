#include "gtest/gtest.h"
#include <gtest/gtest.h>

#include <cardozo.h>
#include <stdexcept>
using namespace cardozo;

#define SKIP_SPARSEMT() \
    if (std::is_same_v<TypeParam, SparseCR>) { \
        GTEST_SKIP() << "SparseCR is readonly"; \
    } \

const std::string filePath{"../../tests/matrix_samples/gr_900_900_crg.mm"};
constexpr int kMatrixSize{900};

static const Matrix<DenseCR> ref = utils::from_mmt_file(filePath);

template<typename T>
class MatrixTest : public testing::Test {
public:

    const Matrix<T> kmt;
    Matrix<T> mt;

    MatrixTest() :
        mt(utils::from_mmt_file(filePath)), 
        kmt(utils::from_mmt_file(filePath)) {
        
    }

};

using StorageTypes = ::testing::Types<DenseCR,SparseCR,StackCR<kMatrixSize, kMatrixSize>>;
TYPED_TEST_SUITE(MatrixTest, StorageTypes);

TYPED_TEST(MatrixTest, CONST_ACCESS_OPERATOR) {

    for(int i = 0; i < this->kmt.getRows(); i++)
    {
        for(int j = 0; j < this->kmt.getCols(); j++)
        {
            EXPECT_EQ(ref(i,j),this->kmt(i,j)) << "Mismatch at (" << i << ", " << j << ")";
        }
    }

}

TYPED_TEST(MatrixTest, CALLING_AT_OOB_BRINGS_EXCEPTION) {

    EXPECT_THROW({
        this->kmt.at(kMatrixSize,kMatrixSize);
    }, std::out_of_range);

}

TYPED_TEST(MatrixTest, REF_ACCESS_OPERATOR) {

    SKIP_SPARSEMT();

    float val = 300;
    int pos = kMatrixSize/2;

    this->mt(pos,pos) = val;

    EXPECT_EQ(this->mt(pos, pos), val);

}

TYPED_TEST(MatrixTest, MATRIX_ELEMENT_SUM)
{
    const Matrix<TypeParam> op = this->kmt + this->kmt;
    auto expectedValue = [&](int i, int j){return this->kmt(i,j)*2;};

    for(int i = 0; i < this->kmt.getRows(); i++)
    {
        for(int j = 0; j < this->kmt.getCols(); j++)
        {
            EXPECT_FLOAT_EQ(op(i,j),expectedValue(i,j));
        }
    }
}

TYPED_TEST(MatrixTest, MATRIX_ELEMENT_SUBTRACTION)
{
    const Matrix<TypeParam> op = this->kmt - this->kmt;
    auto expectedValue = [&](int i, int j){return 0.f;};

    for(int i = 0; i < this->kmt.getRows(); i++)
    {
        for(int j = 0; j < this->kmt.getCols(); j++)
        {
            EXPECT_FLOAT_EQ(op(i,j),expectedValue(i,j));
        }
    }
}

TYPED_TEST(MatrixTest, MATRIX_SCALAR_MULTIPLICATION)
{
    const Matrix<TypeParam> op = this->kmt * 2;
    auto expectedValue = [&](int i, int j){return this->kmt(i,j)*2;};

    for(int i = 0; i < this->kmt.getRows(); i++)
    {
        for(int j = 0; j < this->kmt.getCols(); j++)
        {
            EXPECT_FLOAT_EQ(op(i,j),expectedValue(i,j));
        }
    }
}

TYPED_TEST(MatrixTest, MATRIX_SCALAR_DIVISION)
{
    const Matrix<TypeParam> op = this->kmt / 2;
    auto expectedValue = [&](int i, int j){return this->kmt(i,j)/2;};

    for(int i = 0; i < this->kmt.getRows(); i++)
    {
        for(int j = 0; j < this->kmt.getCols(); j++)
        {
            EXPECT_FLOAT_EQ(op(i,j),expectedValue(i,j));
        }
    }
}

TYPED_TEST(MatrixTest, MATRIX_SUM_SUBTRACT_CANCEL)
{
    const Matrix<TypeParam> op = this->kmt;
    const Matrix<TypeParam> invOp = -this->kmt;

    auto expectedValue = [&](int i, int j){return 0.f;};
    auto invertOperation = [&](int i, int j){return op(i,j)+invOp(i,j);};

    for(int i = 0; i < this->kmt.getRows(); i++)
    {
        for(int j = 0; j < this->kmt.getCols(); j++)
        {
            EXPECT_FLOAT_EQ(invertOperation(i,j), expectedValue(i,j));
        }
    }
}

TYPED_TEST(MatrixTest, MATRIX_SCALAR_PRODUCT_DIVISION_CANCEL)
{
    const Matrix<TypeParam> op = this->kmt*2;

    auto expectedValue = [&](int i, int j){return this->kmt(i,j);};
    auto invertOperation = [&](int i, int j){return op(i,j)*0.5f;};

    for(int i = 0; i < this->kmt.getRows(); i++)
    {
        for(int j = 0; j < this->kmt.getCols(); j++)
        {
            EXPECT_FLOAT_EQ(invertOperation(i,j), expectedValue(i,j));
        }
    }
}

TEST(MatrixTest, STACK_ZERO_INITIALIZATION) {

    Matrix6x6 mt{};

}

TEST(MatrixTest, TRANSPOSE_DENSE_EQ) 
{
    Matrix transposed = algos::transpose(ref);

    for(int i = 0; i < (ref).getRows(); i++) 
    { 
        for(int j = 0; j < (ref).getCols(); j++) 
        { 
          EXPECT_FLOAT_EQ(transposed(i,j),ref(j,i)) << "Mismatch at index " << "(" << i << ", " << j << ")\n"; 
        } 
    } 
}

TEST(MatrixTest, CAN_READ_FROM_FILE) {
    ASSERT_EQ(ref.getCols(), kMatrixSize) << "Matrix column number: " << ref.getCols() << "\n";
    ASSERT_EQ(ref.getRows(), kMatrixSize) << "Matrix row number: " << ref.getRows() << "\n";
}

