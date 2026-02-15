#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "mt_mdata.h"
#include "matrix.h"
#include "vector.h"

namespace {
    using cardozo::MatrixMetadata;
    void parse_header(const std::string& header, MatrixMetadata& metadata)
    {
        std::stringstream check{header};
        std::string intermediate{};

        while(std::getline(check,intermediate,' '))
        {
            if(intermediate.compare("symmetric") == 0)
            {
                metadata = MatrixMetadata::Symmetric;
                break;
            }
        }
    }

    void get_matrix_size(const std::string& s,
            std::size_t& rowNumber, std::size_t&  colNumber, std::size_t& numZeros,
            bool& parseFlag)
    {
        std::stringstream check{s};

        check >> rowNumber >> colNumber >> numZeros;

        parseFlag = true;
    }

}

namespace cardozo::utils {

    Matrix<DenseCR> from_mmt_file(const std::string& file_path) 
    {
        std::ifstream matrixFile{file_path};
        if(!matrixFile)
            throw std::runtime_error("Error Reading File");

        std::string s{};
        std::size_t rowNumber{};
        std::size_t colNumber{};
        std::size_t numZeros{};
        long lineCount{};
        bool parsedSizeFlag{false};

        MatrixMetadata mmeta{MatrixMetadata::Invalid};
        while(std::getline(matrixFile,s,'\n'))
        {
            if(mmeta == MatrixMetadata::Invalid)
                parse_header(s,mmeta);
            else if(s[0] == '%') 
                continue;
            else if(!parsedSizeFlag) {
                get_matrix_size(s, rowNumber, colNumber, numZeros, parsedSizeFlag); 
                break;
            }
            lineCount++;
        }

        Matrix m{static_cast<int>(rowNumber),static_cast<int>(colNumber)};
        while(std::getline(matrixFile, s,'\n'))
        {
            std::stringstream lineStream{s};
            int i{};
            int j{};
            double value{};

            if(lineStream >> i >> j >> value) {
                i--; j--;
            } else {
                std::stringstream errorStream{};
                errorStream << "Failed to parse line " << lineCount << ": " << s <<"\n";
                throw std::runtime_error(errorStream.str());    
            }

            m(i,j) = value;
            if(mmeta == MatrixMetadata::Symmetric)
                m(j,i) = value;

            lineCount++;
        }

        return m;
    }

    void to_csv_fie(const Vector m, const std::string& fileName) {
        std::ofstream file;
        file.open(fileName);

        for (int i = 0; i < m.getLength(); i++)
            file << m(i) << ";";
                
        file.close();
    }
}
