#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <utility>
#include "cardozo.h"

template<typename T>
std::pair<double, T> measure(std::function<T()> lambda)
{
    using namespace std::chrono;
    auto start = steady_clock::now();
    auto value = lambda();
    auto end = steady_clock::now();
    auto time_spent = duration_cast<nanoseconds>(end-start).count();
    return std::make_pair(time_spent, value);
}

int main(int argc, char* argv[]) {

    if(argc != 2)
    {
        std::cerr << "Invalid number of arguments" << std::endl;
        return 1;
    }

    std::random_device dev{};
    std::mt19937 rng{dev()};
    std::normal_distribution<float> dist{0,1e2};
    
    cardozo::Matrix mm = cardozo::utils::from_mmt_file(argv[1]);
    cardozo::Matrix<cardozo::SparseCR> m{mm};

    int manual_nz = 0;
    for(int i = 0; i < mm.getRows(); i++)
    {
        for(int j = 0; j < mm.getCols(); j++)
        {
            float v = m.at(i,j);
            if(v != 0) 
                manual_nz++;
        }
    }
    std::cout << "Non zeros: " << manual_nz << "\n";
    std::cout << "Total elements: " << m.getSize() << "\n";
    cardozo::Vector v{m.getRows()};

    for(int i = 0; i < v.getLength(); i++)
        v(i) = dist(rng);

    auto multiply_res = measure<cardozo::Vector>([&](){
            return cardozo::multiply(m,v);
            });

    std::cout
        << "Matrix (" << m.getRows() << ", " << m.getCols() << ") "
        << "and Vector (" << v.getLength() << ")" << "\n"
        << "Multiplying took " << multiply_res.first << " ns" << "\n"
        ;

    cardozo::Vector b = multiply_res.second;
    cardozo::Vector x{v.getLength()};  

    for(int i = 0; i < x.getLength(); i++) 
        x(i) = dist(rng);

    std::cout << "Starting the solver...\n";
    auto solve_res = measure<cardozo::Vector>([&]() {
            return cardozo::algos::congruentGradient(x, m, b);
            });

    std::cout << "Checking result integrity...\n";
    cardozo::Vector final_result = solve_res.second;

    const double eps_sqr = 1.5 * 1.5;
    for(int i = 0; i < solve_res.second.getLength(); i++)
    {
        float diff = v(i) - final_result(i);
        if (diff*diff >= eps_sqr)
        {
            std::cerr << "Error verifying result, multiplication and solver don't match" << std::endl;
            return 1;
        }
    }

    std::cout << "Done! Solving took " << solve_res.first << " ns" << "\n";
    std::cout << std::endl;

    return 0;
}
