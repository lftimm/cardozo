#include <gtest/gtest.h>

#include <cardozo.h>
using namespace cardozo;


#define EXPECT_MATRIX_EQ(m1, m2) \
    ASSERT_EQ(m1.getCols(),m2.getCols()) << \
        "Matrices don't match in column number: " << \
        m1.getCols() << "vs" << m2.getCols(); \
    ASSERT_EQ(m1.getRows(),m2.getRows()) << \
        "Matrices don't match in row number: " << \
        m1.getRows() << "vs" << m2.getRows(); \
    for(int i = 0; i < m1.getRows(); i++) { \
        for(int j = 0; j < m1.getCols(); j++) {\
            EXPECT_EQ(m1.at(i,j),m2.at(i,j));\
        }\
    }\

const std::string filePath{"../../tests/matrix_samples/gr_900_900_crg.mm"};
constexpr int kMatrixSize{900};

class MatrixTest : public testing:: Test {
protected:


    Matrix<DenseCR> denseMT;
    Matrix<SparseCR> csrMT;
    Transform<kMatrixSize, kMatrixSize> stackMT;

    MatrixTest() :
        denseMT(utils::from_mmt_file(filePath)),
        csrMT(denseMT),
        stackMT(denseMT) {

    }

};

TEST_F(MatrixTest, CAN_READ_FROM_FILE)
{
    Matrix mt{utils::from_mmt_file(filePath)};
    ASSERT_EQ(mt.getCols(), kMatrixSize) << "Matrix column number: " << mt.getCols() << "\n";
    ASSERT_EQ(mt.getRows(), kMatrixSize) << "Matrix row number: " << mt.getRows() << "\n";
}


TEST_F(MatrixTest, DENSE_STACK_ARE_EQUAL) {
    
    EXPECT_MATRIX_EQ(denseMT, stackMT);

}

TEST_F(MatrixTest, DENSE_CSR_ARE_EQUAL) {
    
    EXPECT_MATRIX_EQ(denseMT, csrMT);

}

TEST_F(MatrixTest, STACK_CSR_ARE_EQUAL) {
    
    EXPECT_MATRIX_EQ(csrMT, stackMT);

}
