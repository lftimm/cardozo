#pragma once
#include <fstream>
#include "matrix.h"

namespace cardozo::utils {
    Matrix<DenseCR> from_mmt_file(const std::string& file_path);

    template<typename S>
    void to_csv_fie(const Matrix<S> m,const std::string& fileName) {

        std::ofstream file;
        file.open(fileName);

        for (int i = 0; i < m.getRows(); i++)
        {
            for (int j = 0; j < m.getCols(); j++)
            {
                file << m(i,j) << ";";
            }
            file << "\n";
        }
                
        file.close();
    }

    void to_csv_fie(const Vector m, const std::string& fileName);
}
