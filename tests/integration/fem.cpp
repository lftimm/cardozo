#include <gtest/gtest.h>

#include <cmath>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <stdexcept>

#include "cardozo.h"

using namespace cardozo;

class Material {
private:
    double mE;
public:
    double getE() const { return mE; }

    Material(double E) : mE(E) {};
};

class SectionArea {
public:
    virtual ~SectionArea() = default;
    virtual double I() const = 0;
    virtual double A() const = 0;
};

class CircularArea : public SectionArea {
private:
    double mRadius;
public:

    double I() const override {
        return M_PI * mRadius * mRadius * mRadius * mRadius / 4;
    }

    double A() const override {
        return M_PI * mRadius * mRadius;
    }

    CircularArea(double r) :
        mRadius(r) {
    }
};

class Section {
private:
    double mE;
    double mI;
    double mA;
public:
    double getE() const { return mE; }
    double getI() const { return mI; }
    double getA() const { return mA; }

    Section(const SectionArea& sec, const Material& mat):
        mE{mat.getE()},
        mI{sec.I()},
        mA{sec.A()} {

    }
};



Matrix6x6 localBeamStiffnessMat(const Section& section, double len);
Vector locaclBeamNodalForceMat(double l, double alpha, double p1, double p2);

struct Mesh {
    std::vector<Matrix6x6> ks;
    std::vector<Vector> fs;
    int size;
    int dof;

    Mesh(const Section& sec, int n, double totalLength, double p1, double p2) : size(n) {
        ks.reserve(n);
        fs.reserve(n);
        const double elementSize = totalLength/n;
        for(int i = 0; i < n; i++) 
        {
            ks.emplace_back(localBeamStiffnessMat(sec,elementSize));
            fs.emplace_back(locaclBeamNodalForceMat(elementSize, 0, p1, p2));
        }
        dof = ks[0].getCols()/2;
    }
    
};


void removeDof(Matrix<DenseCR>& mat, Vector& vec, int dof) {

    for (int i = 0; i < mat.getCols(); i++)
    {
        mat(dof,i) = 0;
    }

    for (int i = 0; i < mat.getRows(); i++)
    {
        mat(i,dof) = 0;
    }

    mat(dof,dof) = 1;
    vec(dof) = 0;
}

bool is_positive_definite(const Matrix<DenseCR>& A) {

    auto l = algos::cholesky_decompose(A);
    auto l_t = algos::transpose(l);

    Matrix<DenseCR> a = algos::multiply(l, l_t);

    for(int i = 0; i < A.getRows(); i++)
    {
        for(int j = 0; j < A.getRows(); j++)
        {
            double ex = A(i,j);
            double test = a(i,j); 
            double abs_cerror = std::abs(test - ex);

            if (abs_cerror < 1e-5) 
                continue; 

            double denominator = std::abs(ex);

            if (denominator == 0) 
                denominator = 1;

            double rel_cerror = abs_cerror / denominator;

            if (rel_cerror < 1e-3)
                continue; 

            std::cerr << "Mismatch at (" << i << ", " << j << "):\n"
                << "  Expected: " << ex << "\n"
                << "  Got:      " << test << "\n"
                << "  Abs Diff: " << abs_cerror << "\n"
                << "  Rel cerr:  " << rel_cerror << "\n";

            return false;
        }
    }
     
    std::cerr << "Positive Definite!\n";
    return true;
}

Vector createGlobalForcesVector(const Mesh& mesh) {
    Vector vec{(mesh.size+1)*mesh.dof};

    for (int i = 0; i < mesh.size; i++)
    {
        Vector v = mesh.fs[i];

        for(int j = 0; j < 2*mesh.dof; j++)
        {
            int idx = i*mesh.dof+j;
            vec(idx) += v(j);
        }
    }

    return vec;
}

Vector locaclBeamNodalForceMat(double l, double alpha, double p1, double p2) {
    const double s = sin(alpha);
    const double c = cos(alpha);
    const double c2 = c * c;

    Vector nodalForces{6};

    nodalForces(0) = (p1+0.5*p2)*l*s*c/3;
    nodalForces(1) = (7*p1+3*p2)*l*c2/20;
    nodalForces(2) = (0.5*p1+p2/3)*l*l*c2/10;
    nodalForces(3) = (p1/2+p2)*l*s*c/3;
    nodalForces(4) = (3*p1+7*p2)*l*c2/20;
    nodalForces(5) = -(p1/3+p2/2)*l*l*c2/10;
    
    return nodalForces;
}

Matrix6x6 localBeamStiffnessMat(const Section& section, double len) {
    const double EA = section.getE() * section.getA();
    const double EI = section.getE() * section.getI();
    const double l = len;

    const double k1 = EA / l;
    const double k2 = EI * 12/(l*l*l);
    const double k3 = EI * 6/(l*l);
    const double k4 = EI * 4 / l;
    const double k5 = EI * 2 / l;

    return Matrix6x6({
     {k1,0,0,-k1,0,0},
     {0,k2,k3,0,-k2,k3},
     {0,k3,k4,0,-k3,k5},
     {-k1,0,0,k1,0,0},
     {0,-k2,-k3,0,k2,-k3},
     {0,k3,k5,0,-k3,k4},
    });
}

Matrix<DenseCR> createGlobalStiffnessMatrix(const Mesh& mesh) {

    Matrix ret{(mesh.size+1)*mesh.dof,(mesh.size+1)*mesh.dof};

    for (int m = 0; m < mesh.size; m++)
    {
        const Matrix6x6& locMt = mesh.ks[m];

        for (int i = 0; i < mesh.dof*2; i++)
        {
            for (int j = 0; j < mesh.dof*2; j++)
            {
                int i1 = i + m*mesh.dof;
                int i2 = j + m*mesh.dof;

                ret(i1,i2) += locMt(i,j);
            }
        }
    }

    return ret;
}

TEST(FiniteElement, CANTILEVER_BEAM) {
    const Material steel{210000}; // MN/m²;
    const SectionArea& circular = CircularArea{0.30}; //m
    Section mySection{circular, steel};
    
    int n = 100;
    double totalLength = 10;
    
    Mesh mesh{mySection, n, totalLength, 10, 10};
    Matrix globalMatrix{createGlobalStiffnessMatrix(mesh)};
    Vector globalForces{createGlobalForcesVector(mesh)};

    auto deleteDof = [&](int i) {removeDof(globalMatrix, globalForces, i);};
    deleteDof(0);
    deleteDof(1);
    deleteDof(2);

    if(!is_positive_definite(globalMatrix))
        throw std::logic_error("Not positive definite");

    std::cerr << "\n\n\n";
    std::cerr << "Young Modulus (E): "  << mySection.getE() * 1e-3 << " GPa\n";
    std::cerr << "Area (A): "  << mySection.getA() * 1e4 << " cm²\n";
    std::cerr << "Moment of Inertia (I): "  << mySection.getI()*1e8 << " m⁴\n";
    std::cerr << "Result of an element, size" 
              << "(" << globalMatrix.getRows() << ", " << globalMatrix.getCols() << ")\n";

    Vector u{globalMatrix.getRows()};
    EXPECT_NO_THROW(algos::conjugateGradient(u, globalMatrix, globalForces));
}
