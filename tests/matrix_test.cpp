#include <gtest/gtest.h>

#include <cardozo.h>
#include <stdexcept>
using namespace cardozo;

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

using StorageTypes = ::testing::Types<SparseCR,StackCR<kMatrixSize, kMatrixSize>>;
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

    if (std::is_same_v<TypeParam, SparseCR>) {
        GTEST_SKIP() << "SparseCR is readonly";
    }

    float val = 300;
    int pos = kMatrixSize/2;

    this->mt(pos,pos) = val;

    EXPECT_EQ(this->mt(pos, pos), val);
}



TEST(MatrixTest, CAN_READ_FROM_FILE) {
    ASSERT_EQ(ref.getCols(), kMatrixSize) << "Matrix column number: " << ref.getCols() << "\n";
    ASSERT_EQ(ref.getRows(), kMatrixSize) << "Matrix row number: " << ref.getRows() << "\n";
}

