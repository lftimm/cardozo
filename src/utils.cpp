#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "mt_mdata.h"
#include "matrix.h"

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
        {
            std::cerr << "Error reading file: " << file_path << std::endl;
            std::exit(1);
        }

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
        while(std::getline(matrixFile,s,'\n'))
        {
            std::stringstream lineStream{s};
            int i{};
            int j{};
            float value{};

            if(lineStream >> i >> j >> value) {
                i--; j--;
            } else {
                std::cerr << "Failed to parse line " << lineCount << ": " << s <<"\n";
                std::exit(1);    
            }

            m(i,j) = value;
            if(mmeta == MatrixMetadata::Symmetric)
                m(j,i) = value;

            lineCount++;
        }

        return m;
    }
}
